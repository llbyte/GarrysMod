#include "CConfig.hpp"

#include <Windows.h>

#include "DllLauncher/CDllLauncher.hpp"

static CConfig g_Config{};

auto CConfig::Initialize( ) -> bool {
    const std::string configDir = GetDllDir() + "/configs";
    CreateDirectoryA(configDir.c_str(), nullptr);

    return true;
}

auto CConfig::Save() -> bool {

    return true;
}


auto GetConfig() -> CConfig* {
    return &g_Config;
}