#pragma once

#include <mutex>
#include <Windows.h>

#define ENABLE_CONSOLE_DEBUG 1

class CLog final {
public:
    auto Initialize() -> void;
    auto Destroy() -> void;
    auto AddLog( const char* fmt, ... ) -> void;

private:
    std::recursive_mutex m_Lock;

#if ENABLE_CONSOLE_DEBUG == 1
    FILE* COutputHandle = nullptr;
    FILE* CErrorHandle = nullptr;
#endif
    HANDLE hLogFile = INVALID_HANDLE_VALUE;

};

auto GetLog() -> CLog*;

#define LOG( fmt, ... ) GetLog()->AddLog( fmt, __VA_ARGS__ )