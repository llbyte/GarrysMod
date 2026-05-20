#include "CCrashLog.hpp"

#include <Common/Log/CLog.hpp>
#include <Psapi.h>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <mutex>

#include "DllLauncher/CDllLauncher.hpp"

static CCrashLog g_CCrashLog{};

auto IsBadPtr( const PVOID Ptr ) -> bool {
	MEMORY_BASIC_INFORMATION mbi{};

	if ( VirtualQuery( Ptr, &mbi, sizeof( mbi )) ) {
		constexpr DWORD mask = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

		bool b = !( mbi.Protect & mask );

		if ( mbi.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) )
			b = true;

		return b;
	}

	return true;
}

auto CCrashLog::Initialize() -> void {
	m_pVecExcHandler = AddVectoredExceptionHandler(1, VectoredExceptionHandler);

	if ( !m_pVecExcHandler ) {
        MessageBoxW(
        	nullptr,
        	L"Error AddVectoredExceptionHandler",
        	L"Error",
        	MB_ICONERROR
        );
	}
}

auto CCrashLog::Destroy() -> void {
	if (m_pVecExcHandler) {
		RemoveVectoredExceptionHandler(m_pVecExcHandler);
		m_pVecExcHandler = nullptr;
	}
}

auto WINAPI CCrashLog::VectoredExceptionHandler( PEXCEPTION_POINTERS pExceptionInfo )->LONG {
    const auto ExceptionCode = pExceptionInfo->ExceptionRecord->ExceptionCode;
    auto ExceptionAddress = pExceptionInfo->ExceptionRecord->ExceptionAddress;
    const auto CheatHinstance = GetDllLauncher()->GetDllImage();

    std::string ModuleName;

    if ( ExceptionCode == STATUS_ACCESS_VIOLATION ||
        ExceptionCode == STATUS_STACK_BUFFER_OVERRUN ||
        ExceptionCode == STATUS_STACK_OVERFLOW ||
        ExceptionCode == STATUS_BREAKPOINT
    ) {
    	const auto hProcess = OpenProcess(
    		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ ,
    		false ,
    		GetCurrentProcessId()
    	);
	    if ( hProcess ) {
            char CrashModuleNameTmp[MAX_PATH] = {};

            if ( GetMappedFileNameA( hProcess , ExceptionAddress , CrashModuleNameTmp , MAX_PATH ) > 0 ) {
                std::string CrashModuleName = CrashModuleNameTmp;
                CrashModuleName = CrashModuleName.substr( CrashModuleName.find_last_of( '\\' ) + 1 );

                const auto ModuleHinstance = GetModuleHandleA( CrashModuleName.c_str() );
                const auto ModuleCrashOffset = reinterpret_cast<uintptr_t>(ExceptionAddress) - reinterpret_cast<uintptr_t>(ModuleHinstance);

                GetCrashLog()->WriteCrashLogFile( "Exception Handle: %p\n", ModuleHinstance );
                GetCrashLog()->WriteCrashLogFile( "Exception Module: %s\n", CrashModuleName.c_str() );
                GetCrashLog()->WriteCrashLogFile( "Exception Offset: %X\n", ModuleCrashOffset );
            }

            GetCrashLog()->WriteCrashLogFile( "Exception Code: %X\n", ExceptionCode );
            GetCrashLog()->WriteCrashLogFile( "Exception Thread: %X\n", GetCurrentThreadId() );
            GetCrashLog()->WriteCrashLogFile( "Exception Address: %p\n\n", ExceptionAddress );

            GetCrashLog()->WriteCrashLogFile( "Rax: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rax) );
            GetCrashLog()->WriteCrashLogFile( "Rcx: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rcx) );
            GetCrashLog()->WriteCrashLogFile( "Rdx: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rdx) );
            GetCrashLog()->WriteCrashLogFile( "Rbx: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rbx) );
            GetCrashLog()->WriteCrashLogFile( "Rsp: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rsp) );
            GetCrashLog()->WriteCrashLogFile( "Rbp: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rbp) );
            GetCrashLog()->WriteCrashLogFile( "Rsi: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rsi) );
            GetCrashLog()->WriteCrashLogFile( "Rdi: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->Rdi) );
            GetCrashLog()->WriteCrashLogFile( "R8: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R8) );
            GetCrashLog()->WriteCrashLogFile( "R9: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R9) );
            GetCrashLog()->WriteCrashLogFile( "R10: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R10) );
            GetCrashLog()->WriteCrashLogFile( "R11: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R11) );
            GetCrashLog()->WriteCrashLogFile( "R12: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R12) );
            GetCrashLog()->WriteCrashLogFile( "R13: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R13) );
            GetCrashLog()->WriteCrashLogFile( "R14: %p\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R14) );
            GetCrashLog()->WriteCrashLogFile( "R15: %p\n\n", reinterpret_cast<PVOID>(pExceptionInfo->ContextRecord->R15) );

            if ( IsCrashCheat( ExceptionAddress ) ) {
                auto CheatOffset = reinterpret_cast<uintptr_t>(ExceptionAddress) - reinterpret_cast<uintptr_t>(CheatHinstance);

                GetCrashLog()->WriteCrashLogFile( "%s Offset: %X\n", "InternalBase" , static_cast<uint32_t>(CheatOffset) );
            }

            PVOID pCallStackList[256] = { nullptr };

            if ( const auto NumFrameCaptured = RtlCaptureStackBackTrace( 4 , 256 , pCallStackList , nullptr ) ) {
                GetCrashLog()->WriteCrashLogFile( "\nCALLSTACK:\n" );

                for ( uint32_t i = 0; i < NumFrameCaptured; i++ ) {
                    auto pStack = pCallStackList[i];

                    if ( IsCrashCheat( pStack ) ) {
                        const auto CheatOffset = reinterpret_cast<uintptr_t>(pStack) - reinterpret_cast<uintptr_t>(CheatHinstance);

                        GetCrashLog()->WriteCrashLogFile( "CallStack (%i): %p (%s) -> %X\n", i , pStack , "Internal Base" , static_cast<uint32_t>(CheatOffset) );
                    }
                    else {
                        char ModuleNameTmp[MAX_PATH] = { 0 };

                        if ( pStack && GetMappedFileNameA( hProcess , pStack , ModuleNameTmp , MAX_PATH ) > 0 ) {
                            ModuleName = ModuleNameTmp;
                            ModuleName = ModuleName.substr( ModuleName.find_last_of( '\\' ) + 1 );

                            const auto ModuleHinstance = GetModuleHandleA( ModuleName.c_str() );
                            const auto ModuleCrashOffset = reinterpret_cast<uintptr_t>(pStack) - reinterpret_cast<uintptr_t>(ModuleHinstance);

                        	GetCrashLog()->WriteCrashLogFile( "CallStack (%i): %p (%s) -> %X\n", i , pStack , ModuleName.c_str() , static_cast<uint32_t>(ModuleCrashOffset) );
                        }
                    }
                }
            }

           GetCrashLog()->WriteCrashLogFile( "\n\nFULLSTACK:\n" );

            for ( uint32_t i = 0; i < 256; i++ ) {
                const auto RSP = pExceptionInfo->ContextRecord->Rsp;
                const auto RSP_Ptr = static_cast<uintptr_t>(RSP) + ( i * sizeof( PVOID ) );

                if ( IsBadPtr( reinterpret_cast<PVOID>(RSP_Ptr) ) == false ) {
                    const auto RSP_Data = *reinterpret_cast<uintptr_t *>(RSP_Ptr);

                    if ( IsCrashCheat( reinterpret_cast<PVOID>(RSP_Data) ) ) {
                        const auto CheatOffset = static_cast<uintptr_t>(RSP_Data) - reinterpret_cast<uintptr_t>(CheatHinstance);

                        GetCrashLog()->WriteCrashLogFile( "Stack (%i): %p (%s) -> %X\n", i , reinterpret_cast<PVOID>(RSP_Data) , "InternalBase" , static_cast<uint32_t>(CheatOffset) );
                    } else {
                        char ModuleNameTmp[MAX_PATH] = {};

                        if ( GetMappedFileNameA( hProcess , reinterpret_cast<PVOID>(RSP_Data) , ModuleNameTmp , MAX_PATH ) > 0 ) {
                            ModuleName = ModuleNameTmp;
                            ModuleName = ModuleName.substr( ModuleName.find_last_of( '\\' ) + 1 );

                            const auto ModuleHinstance = GetModuleHandleA( ModuleName.c_str() );
                            const auto ModuleCrashOffset = static_cast<uintptr_t>(RSP_Data) - reinterpret_cast<uintptr_t>(ModuleHinstance);

                            GetCrashLog()->WriteCrashLogFile( "Stack (%i): %p (%s) -> %X\n", i , reinterpret_cast<PVOID>(RSP_Data) , ModuleName.c_str() , static_cast<uint32_t>(ModuleCrashOffset) );
                        }
                        else {
                            GetCrashLog()->WriteCrashLogFile( "Stack (%i): %p\n", i , reinterpret_cast<PVOID>(RSP_Data) );
                        }
                    }
                } else {
                    break;
                }
            }

            CloseHandle( hProcess );
        }
    }

	return EXCEPTION_CONTINUE_SEARCH;
}

auto CCrashLog::WriteCrashLogFile( const char* fmt , ... ) -> void {
	std::lock_guard lk( m_Lock );

	char buff[4096] = {};

	va_list args;
	va_start( args , fmt );
	vsnprintf( buff, sizeof( buff ) - 1, fmt, args );
	va_end( args );

	LOG( "%s", buff );
}

auto CCrashLog::IsCrashCheat( PVOID Address ) -> bool {
	const auto CheatStart = GetDllLauncher()->GetDllImage();
	const auto CheatEnd = CheatStart + GetDllLauncher()->GetSizeOfImage();

	if (
		reinterpret_cast<uintptr_t>(Address) > reinterpret_cast<uintptr_t>(CheatStart) &&
		reinterpret_cast<uintptr_t>(Address) < reinterpret_cast<uintptr_t>(CheatEnd)
	)
		return true;

	return false;
}

auto CCrashLog::GetCurrentDateTime() -> std::wstring {
	const time_t now = time( nullptr );
	tm tstruct = {};
	char buf[80] = {};

	localtime_s( &tstruct , &now );
	strftime( buf , sizeof( buf ) , "%d.%m.%Y.%H.%M.%S", &tstruct );

	std::string StrBuf( buf );

	return { StrBuf.begin(), StrBuf.end() };
}

auto GetCrashLog() -> CCrashLog* {
	return &g_CCrashLog;
}