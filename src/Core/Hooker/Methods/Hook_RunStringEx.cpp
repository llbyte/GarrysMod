#include "Hook_RunStringEx.hpp"

#include <Common/Log/CLog.hpp>
#include <DllLauncher/CDllLauncher.hpp>

auto Hook_RunStringEx(
    void* pLuaInterface,
    const char* pIdentifier,
    const char* pPath,
    const char* pCode,
    const bool bSetScriptVars,
    const bool bLogErrors,
    const bool bPopOnError,
    const bool bPopResults
) -> char {

    // LOG("[dumper] RunStringEx: Identifier: %s, Code Length: %zu\n",
    //     pIdentifier ? pIdentifier : "null",
    //     pCode ? strlen(pCode) : 0
    // );

    // const auto folder = GetDllLauncher()->GetDllDir();
    //
    // if (pPath && pCode) {
    //     const auto dumpFilePath = std::filesystem::path(folder) / "dumps" / pIdentifier;
    //
    //     std::filesystem::create_directories(dumpFilePath.parent_path());
    //
    //     if (std::ofstream dumpFile(dumpFilePath); dumpFile.is_open()) {
    //         dumpFile << pCode;
    //     }
    // }

    return RunStringEx_o(
        pLuaInterface,
        pIdentifier,
        pPath,
        pCode,
        bSetScriptVars,
        bLogErrors,
        bPopOnError,
        bPopResults
    );
}