#include "Hook_PaintTraverse.hpp"

#include <Core/SDK/SDK.hpp>
#include <Client/Features/LuaExecutor/CLuaExecutor.hpp>

auto Hook_PaintTraverse(
    void* thisptr,
    void* panel,
    const bool forceRepaint,
    const bool allowForce
) -> void {
    const auto luaShared = SDK::Interfaces::LuaShared( );

    if ( const auto lua = luaShared->GetLuaInterface( CLIENT ) ) {
        if ( const auto script = GetLuaExecutor()->Pop( ) ) {
            lua->RunStringEx(
                "LuaExecutor",
                "",
                script->c_str( ),
                true,
                false,
                false,
                false
            );
        }
    }

    PaintTraverse_o(thisptr, panel, forceRepaint, allowForce);
}