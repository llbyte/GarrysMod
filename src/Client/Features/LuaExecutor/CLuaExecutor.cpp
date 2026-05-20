#include "CLuaExecutor.hpp"

#include <utility>

static CLuaExecutor g_LuaExecutor;

auto CLuaExecutor::Execute( std::string code ) -> void {
    if ( code.empty( ) )
        return;

    std::lock_guard lock( m_Mutex );
    m_Queue.push( std::move( code ) );
}

auto CLuaExecutor::Pop( ) -> std::optional<std::string> {
    std::lock_guard lock( m_Mutex );

    if ( m_Queue.empty() )
        return std::nullopt;

    auto code = std::move( m_Queue.front( ) );
    m_Queue.pop( );

    return code;
}

auto GetLuaExecutor() -> CLuaExecutor* {
    return &g_LuaExecutor;
}