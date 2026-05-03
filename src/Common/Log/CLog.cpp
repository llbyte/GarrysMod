#include "CLog.hpp"
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <mutex>

#include "DllLauncher/CDllLauncher.hpp"

static CLog g_Log{};

auto CLog::Initialize() -> void {
#if ENABLE_CONSOLE_DEBUG == 1
    AllocConsole();

    SetConsoleCP( CP_UTF8 );
    SetConsoleOutputCP( CP_UTF8 );

    HANDLE hConsoleOut = GetStdHandle( STD_OUTPUT_HANDLE );
    const int fdOut = _open_osfhandle( reinterpret_cast<intptr_t>(hConsoleOut), _O_TEXT );
    COutputHandle = _fdopen( fdOut, "w" );

    HANDLE hConsoleErr = GetStdHandle( STD_ERROR_HANDLE );
    const int fdErr = _open_osfhandle( reinterpret_cast<intptr_t>(hConsoleErr), _O_TEXT );
    CErrorHandle = _fdopen( fdErr, "w" );

    freopen_s( &COutputHandle, "CONOUT$", "w", stderr );
    freopen_s( &CErrorHandle, "CONOUT$", "w", stdout );

    std::cout.clear();
    std::cerr.clear();
#endif

    const auto logPath = GetDllDir() + "\\debug.log";
    hLogFile = CreateFileA(
        logPath.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
}

auto CLog::Destroy() -> void {
#if ENABLE_CONSOLE_DEBUG == 1
    if ( CErrorHandle ) {
        fflush( CErrorHandle );
        fclose( CErrorHandle );
        CErrorHandle = nullptr;
    }

    if ( COutputHandle ) {
        fflush( COutputHandle );
        fclose( COutputHandle );
        COutputHandle = nullptr;
    }

    FreeConsole();
#endif

    CloseHandle( hLogFile );
}

auto CLog::AddLog( const char* fmt, ... ) -> void {
    std::lock_guard lk( m_Lock );

    char buff[4096] = {};

    va_list args;
    va_start( args, fmt );
    vsnprintf( buff, sizeof( buff ) - 1, fmt , args );
    va_end( args );

#if ENABLE_CONSOLE_DEBUG == 1
    printf( "%s", buff );
#endif
    WriteFile( hLogFile, buff, lstrlenA( buff ), nullptr, nullptr );
}

auto GetLog() -> CLog* {
    return &g_Log;
}