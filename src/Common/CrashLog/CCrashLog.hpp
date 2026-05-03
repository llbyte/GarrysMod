#pragma once

#include <Windows.h>
#include <mutex>

class CCrashLog final {
public:
    auto Initialize() -> void;
    auto Destroy() -> void;

private:
    static LONG WINAPI VectoredExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo);

    auto WriteCrashLogFile(const char* fmt, ...) -> void;
    static auto GetCurrentDateTime() -> std::wstring;
    static auto IsCrashCheat(PVOID Address) -> bool;

    std::recursive_mutex m_Lock;
    PVOID m_pVecExcHandler = nullptr;
};

auto GetCrashLog() -> CCrashLog*;