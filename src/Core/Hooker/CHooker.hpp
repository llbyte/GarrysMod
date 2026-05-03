#pragma once

#include <vector>
#include <Windows.h>

#include <Common/Pattern/CBasePattern.hpp>

struct HookData {
    CBasePattern m_Pattern;
    LPVOID m_pDetour = nullptr;
    LPVOID* m_pOriginal = nullptr;
    bool m_bSkipIfNotFound = false;
    bool m_bSkipError = false;
};

class CHooker final {
public:
    auto Initialize() -> bool;
    auto InstallSecondHook() -> bool;
    auto Destroy() -> void;

private:
    auto InstallHooks() -> bool;

    bool m_bInitialized = false;
    std::vector<HookData> m_Hooks;
};

auto GetHooker() -> CHooker*;