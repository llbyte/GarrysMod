#include "CDllLauncher.hpp"

#include <Common/Log/CLog.hpp>
#include <Common/CrashLog/CCrashLog.hpp>
#include <Core/SDK/SDK.hpp>
#include <Core/Hooker/CHooker.hpp>
#include <Core/SDK/Interface/CClientEntityList.hpp>
#include <Core/SDK/Interface/CLuaShared.hpp>
#include <Core/Menu/CMenuRender.hpp>

static CDllLauncher g_CDllLauncher{};

auto CDllLauncher::OnDllMain( const void*, HINSTANCE hInstance ) -> void {
    m_hDllImage = hInstance;
    m_SizeofImage = reinterpret_cast<PIMAGE_NT_HEADERS>(
        reinterpret_cast<std::uint8_t*>(m_hDllImage) +
        reinterpret_cast<PIMAGE_DOS_HEADER>(m_hDllImage)->e_lfanew
    )->OptionalHeader.SizeOfImage;

    char szGameFile[MAX_PATH] = { };
    GetModuleFileNameA( nullptr , szGameFile , MAX_PATH );

    m_DllDir = "C:\\Logs";
    m_GMODDir = szGameFile;
    m_GMODDir = m_GMODDir.substr( 0 , m_GMODDir.find_last_of( "\\/" ) );
    m_GMODDir += '\\';

    CreateDirectoryA(m_DllDir.c_str(), nullptr);

    CreateThread(
        nullptr,
        0,
        StartCheatThread,
        nullptr,
        0,
        nullptr
    );
}

auto WINAPI CDllLauncher::StartCheatThread( LPVOID ) -> DWORD {
    GetCrashLog()->Initialize();
	GetLog()->Initialize();

    if ( !GetHooker()->Initialize() ) {
        LOG( "[error] Hooker: Initialize\n" );
        return false;
    }

    if ( !GetHooker()->InstallSecondHook() ) {
        LOG( "[error] Hooker: InstallSecondHook\n" );
        return false;
    }

    // Interfaces

#define CHECK_INTERFACE( x ) \
    if ( !( x ) ) { \
        LOG( "[error] Interface: " #x "\n" ); \
        return false; \
    }

    CHECK_INTERFACE( SDK::Interfaces::ClientEntityList() );
    CHECK_INTERFACE( SDK::Interfaces::EngineClient() );
    CHECK_INTERFACE( SDK::Interfaces::MaterialSystem() );
    CHECK_INTERFACE( SDK::Interfaces::LuaShared() );

#undef CHECK_INTERFACE

    // LOG( "TickRate: %f\n", SDK::Pointers::GlobalVars()->GetTickrate() );

    LOG( "[info] Cheat initialized\n" );

    // LOG( " Clients: %i", SDK::Interfaces::EngineClient()->GetMaxClients() );

    while (!(GetAsyncKeyState(VK_END) & 1)) {
        Sleep(100);
    }

    FreeLibraryAndExitThread(
        GetDllLauncher()->GetDllImage(),
        0
    );

    return true;
}

auto CDllLauncher::OnDestroy() -> void {
    std::call_once(
        m_bDestroyed,
        [] {
            GetLog()->Destroy();
            GetHooker()->Destroy();
            GetMenuRender()->Destroy();
            GetCrashLog()->Destroy();
        }
    );
}

auto GetDllDir()->std::string& {
    return GetDllLauncher()->m_DllDir;
}

auto GetGMODDir() -> std::string {
    return GetDllLauncher()->m_GMODDir;
}

auto GetDllLauncher() -> CDllLauncher* {
    return &g_CDllLauncher;
}
