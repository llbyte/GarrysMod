#pragma once

#include <cstdint>
#include <Windows.h>

enum PatternSearchType : int32_t {
    SEARCH_TYPE_NONE,
    SEARCH_TYPE_PTR,
    SEARCH_TYPE_PROC
};

class IBasePattern {
protected:
    ~IBasePattern() = default;

public:
    virtual bool Search( bool SkipError ) = 0;
    virtual PVOID GetFunction() = 0;
    virtual const char* GetPatternName() = 0;
    virtual const char* GetDllName() = 0;
};

class CBasePattern final : public IBasePattern {
public:
    CBasePattern(
        const char* szPatternName,
        const char* szPattern,
        const char* szDll,
        uint32_t Offset = 0,
        PatternSearchType Type = SEARCH_TYPE_NONE
    );

    bool Search( bool SkipError ) override;
    PVOID GetFunction() override;
    const char* GetPatternName() override;
    const char* GetDllName() override;

private:
    static uintptr_t FindPattern(const char* moduleName, const char *pattern, const uint32_t offset = 0) {
        const HMODULE hModule = GetModuleHandleA(moduleName);
        if (!hModule)
            return 0;

        const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
        const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
            reinterpret_cast<uintptr_t>(hModule) + dosHeader->e_lfanew
        );

        const auto start = reinterpret_cast<uintptr_t>(hModule);
        const uintptr_t end = start + ntHeaders->OptionalHeader.SizeOfImage;

        const char* pat = pattern;
        uintptr_t firstMatch = 0;

        for (uintptr_t cur = start; cur < end; ++cur) {
            if (*pat == '?' || *reinterpret_cast<uint8_t*>(cur) == static_cast<uint8_t>(strtoul(pat, nullptr, 16))) {
                if (!firstMatch) firstMatch = cur;
                if (!pat[1] || !pat[2]) return firstMatch + offset;
                pat += *pat == '?' ? 2 : 3;
            } else {
                pat = pattern;
                firstMatch = 0;
            }
        }
        return 0;
    }

    const char* PatternName = nullptr;
    const char* Pattern = nullptr;
    const char* Dll = nullptr;

    PVOID pFunction = nullptr;
    uint32_t dwOffset = 0;
    PatternSearchType m_Type = SEARCH_TYPE_NONE;
};