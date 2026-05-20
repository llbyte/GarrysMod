#pragma once

#include <optional>
#include <queue>
#include <string>
#include <mutex>

class CLuaExecutor final {
public:
    auto Execute(std::string code) -> void;

private:
    friend auto Hook_PaintTraverse(
        void* thisptr,
        void* panel,
        bool forceRepaint,
        bool allowForce
    ) -> void;

    auto Pop() -> std::optional<std::string>;

private:
    std::queue<std::string> m_Queue;
    std::mutex m_Mutex;
};

auto GetLuaExecutor() -> CLuaExecutor*;