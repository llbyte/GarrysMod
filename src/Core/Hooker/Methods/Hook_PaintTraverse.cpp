#include "Hook_PaintTraverse.hpp"

#include "Common/Log/CLog.hpp"
#include "Core/SDK/SDK.hpp"
#include "Core/SDK/Types/C_BaseEntity.hpp"

auto Hook_PaintTraverse(
    void* thisptr,
    void* panel,
    const bool forceRepaint,
    const bool allowForce
) -> void {
    PaintTraverse_o(thisptr, panel, forceRepaint, allowForce);

    // static ULONGLONG lastListTime = 0;
    // const ULONGLONG now = GetTickCount64();
    // if (now - lastListTime < 5000)
    //     return;
    // lastListTime = now;


    // auto lua = SDK::Interfaces::LuaShared()->GetLuaInterface(CLIENT);
    // if ( !lua ) {
    //     LOG("Failed to get LuaShared()");
    //     return;
    // }
    //
    // auto local = SDK::Interfaces::ClientEntityList()->GetBaseEntity(SDK::Interfaces::EngineClient()->GetLocalPlayer());
    //
    // local->PushEntity();
    //
    // lua->GetField(-1, "GetName");
    //
    // lua->Push(-2);
    // lua->Call(1, 1);
    // const char* value = lua->GetString(-1);
    //
    // lua->Pop(2);
    //
    // LOG("Localplayer name: %s", value);
}
