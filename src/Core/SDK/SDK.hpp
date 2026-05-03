#pragma once

#include <Common/Math/Matrix.hpp>

#include <Core/SDK/Interface/CClientEntityList.hpp>
#include <Core/SDK/Interface/CLuaShared.hpp>
#include <Core/SDK/Interface/CMaterialSystem.hpp>
#include <Core/SDK/Update/CGlobalVars.hpp>
#include <Core/SDK/Interface/CEngineClient.hpp>

#define CLIENT_DLL "client.dll"
#define ENGINE_DLL "engine.dll"
#define VGUI2_DLL "vgui2.dll"
#define MATERIAL_SYSTEM_DLL "materialsystem.dll"
#define LUA_DLL "lua_shared.dll"
#define GAMEOVERLAYRENDER64_DLL "gameoverlayrenderer64.dll"

namespace SDK {
    extern Matrix ViewMatrix;

    class Interfaces {
    public:
        static auto ClientEntityList() -> CClientEntityList*;
        static auto EngineClient() -> CEngineClient*;
        static auto MaterialSystem() -> CMaterialSystem*;
        static auto LuaShared() -> CLuaShared*;

    private:
        static CClientEntityList* g_pClientEntityList;
        static CEngineClient* g_pEngineClient;
        static CMaterialSystem* g_pMaterialSystem;
        static CLuaShared* g_pLuaShared;
    };

    class Pointers {
    public:
        static auto GlobalVars() -> CGlobalVars*;
        static auto ViewMatrix() -> Matrix*;

    private:
        static CGlobalVars* g_pCGlobalVars;
    };

}