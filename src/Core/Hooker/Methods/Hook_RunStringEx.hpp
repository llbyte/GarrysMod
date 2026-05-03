#pragma once

using RunStringEx_t = char(__fastcall*)(
    void* pLuaInterface,
    const char* pIdentifier,
    const char* pPath,
    const char* pCode,
    bool bSetScriptVars,
    bool bLogErrors,
    bool bPopOnError,
    bool bPopResults
);

auto Hook_RunStringEx(
    void* pLuaInterface,
    const char* pIdentifier,
    const char* pPath,
    const char* pCode,
    bool bSetScriptVars,
    bool bLogErrors,
    bool bPopOnError,
    bool bPopResults
) -> char;

inline RunStringEx_t RunStringEx_o = nullptr;