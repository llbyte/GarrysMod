#include "CHooker.hpp"

#include <cinttypes>
#include <MinHook.h>
#include <Common/Log/CLog.hpp>
#include <Core/SDK/SDK.hpp>

#include "Methods/Hook_OverrideView.hpp"
#include "Methods/Hook_Paint.hpp"
#include "Methods/Hook_Present.hpp"
#include "Methods/Hook_RunStringEx.hpp"
#include "Methods/Hook_PaintTraverse.hpp"
#include "Methods/Hook_RenderView.hpp"
#include "Methods/Hook_CreateMove.hpp"

static CHooker g_CHooker{};

auto CHooker::Initialize() -> bool {
    if ( m_bInitialized )
        return true;

    if ( MH_Initialize() == MH_OK ) {
        m_bInitialized = true;
        return true;
    }

    return false;
}

auto CHooker::InstallSecondHook() -> bool {
    m_Hooks = {
        {
            { "GameOverlayRenderer64::PresentOverlay", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 8B A4 24", GAMEOVERLAYRENDER64_DLL },
            reinterpret_cast<LPVOID>( &Hook_Present ),
            reinterpret_cast<LPVOID*>( &Present_o )
        },
        {
            { "IClientMode::CreateMove", "40 53 48 83 EC ? 0F 29 74 24 ? 49 8B D8", CLIENT_DLL },
            reinterpret_cast<LPVOID>( &Hook_CreateMove ),
            reinterpret_cast<LPVOID*>( &CreateMove_o )
        },
        // {
        //     { "CModelRender:::DrawModelExecute", "40 55 53 56 41 54 41 55 41 56 41 57", ENGINE_DLL },
        //     reinterpret_cast<LPVOID>( &Hook_DrawModelExecute ),
        //     reinterpret_cast<LPVOID*>( &DrawModelExecute_o )
        // },
        {
            { "VPanel::PaintTraverse", "48 89 5C 24 ? 57 48 83 EC ? ? ? ? 41 0F B6 D9", VGUI2_DLL },
            reinterpret_cast<LPVOID>( &Hook_PaintTraverse ),
            reinterpret_cast<LPVOID*>( &PaintTraverse_o )
        },
        {
            { "CEngineVGui::Paint", "48 83 EC ? 48 89 6C 24 ? 48 8B E9", ENGINE_DLL },
            reinterpret_cast<LPVOID>( &Hook_Paint ),
            reinterpret_cast<LPVOID*>( &Paint_o )
        },
        {
            { "CLuaInterface::RunStringEx", "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F0", LUA_DLL },
            reinterpret_cast<LPVOID>( &Hook_RunStringEx ),
            reinterpret_cast<LPVOID*>( &RunStringEx_o )
        },
        {
            { "Unknown::OverrideView", "40 55 53 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B DA", CLIENT_DLL },
            reinterpret_cast<LPVOID>( &Hook_OverrideView ),
            reinterpret_cast<LPVOID*>( &OverrideView_o )
        },
        {
            { "CViewRender::RenderView", "4C 8B DC 55 53 56 41 54 49 8D AB", CLIENT_DLL },
            reinterpret_cast<LPVOID>( &Hook_RenderView ),
            reinterpret_cast<LPVOID*>( &RenderView_o ),
            true
        }
    };

    return InstallHooks();
}

auto CHooker::InstallHooks() -> bool {
    for ( auto&[m_Pattern, m_pDetour, m_pOriginal, m_bSkipIfNotFound, m_bSkipError] : m_Hooks ) {
        while ( !GetModuleHandleA( m_Pattern.GetDllName() ) )
            Sleep( 1 );

        if ( !m_Pattern.Search( m_bSkipError ) ) {
            if ( !m_bSkipError )
                LOG( "[hooker] Pattern scan failed for '%s'\n", m_Pattern.GetPatternName() );

            if ( !m_bSkipIfNotFound )
                return false;

            continue;
        }

        const auto status = MH_CreateHook(
            m_Pattern.GetFunction(),
            m_pDetour,
            m_pOriginal
        );

        if ( status != MH_OK ) {
            LOG(
                "[hooker] MinHook::CreateHook failed for '%s' (status: %d)\n",
                m_Pattern.GetPatternName(),
                status
            );
            return false;
        }

        LOG( "[hooker] Successfully hooked '%s' at address: 0x%" PRIxPTR "\n", m_Pattern.GetPatternName(), m_Pattern.GetFunction() );
    }

    MH_EnableHook( nullptr );
    m_Hooks.clear();

    return true;
}

auto CHooker::Destroy() -> void {
    if ( m_bInitialized ) {
        MH_DisableHook( nullptr );
        MH_Uninitialize();
        m_bInitialized = false;
    }
}

auto GetHooker() -> CHooker* {
    return &g_CHooker;
}