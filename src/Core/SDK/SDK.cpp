#include "SDK.hpp"

#include <Common/Log/CLog.hpp>
#include <Common/Pattern/CBasePattern.hpp>
#include <Common/Math/Matrix.hpp>

#include <Core/SDK/Interface/Interface.hpp>

namespace SDK {
	CClientEntityList* Interfaces::g_pClientEntityList = nullptr;
	CEngineClient* Interfaces::g_pEngineClient = nullptr;
	CMaterialSystem* Interfaces::g_pMaterialSystem = nullptr;
	CLuaShared* Interfaces::g_pLuaShared = nullptr;

	Matrix Globals::g_ViewMatrix{};

	auto Interfaces::ClientEntityList() -> CClientEntityList* {
		if ( !g_pClientEntityList ) {
			const CreateInterfaceFn pfnFactory = CaptureFactory( CLIENT_DLL );
			g_pClientEntityList = CaptureInterface<CClientEntityList>( pfnFactory, CLIENT_ENTITYLIST_VERSION );
		}

		return g_pClientEntityList;
	}

	auto Interfaces::EngineClient() -> CEngineClient* {
		if ( !g_pEngineClient ) {
			const CreateInterfaceFn pfnEngine = CaptureFactory( ENGINE_DLL );
			g_pEngineClient = CaptureInterface<CEngineClient>( pfnEngine, ENGINE_CLIENT_VERSION );
		}
		return g_pEngineClient;
	}

	auto Interfaces::MaterialSystem() -> CMaterialSystem* {
		if ( !g_pMaterialSystem) {
			const CreateInterfaceFn pfnEngine = CaptureFactory( MATERIAL_SYSTEM_DLL );
			g_pMaterialSystem = CaptureInterface<CMaterialSystem>( pfnEngine, MATERIAL_SYSTEM_VERSION );
		}
		return g_pMaterialSystem;
	}

	auto Interfaces::LuaShared() -> CLuaShared* {
		if ( !g_pLuaShared ) {
			const CreateInterfaceFn pfnFactory = CaptureFactory( LUA_DLL );
			g_pLuaShared = CaptureInterface<CLuaShared>( pfnFactory, LUA_SHARED_VERSION );
		}

		return g_pLuaShared;
	}

	auto Globals::ViewMatrix() -> Matrix* {
		return &g_ViewMatrix;
	}
}