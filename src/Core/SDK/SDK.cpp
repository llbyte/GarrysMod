#include "SDK.hpp"

#include <Common/Log/CLog.hpp>
#include <Common/Pattern/CBasePattern.hpp>
#include <Common/Math/Matrix.hpp>

#include <Core/SDK/Interface/Interface.hpp>

namespace SDK {
	Matrix ViewMatrix{};

	CClientEntityList* Interfaces::g_pClientEntityList = nullptr;
	CEngineClient* Interfaces::g_pEngineClient = nullptr;
	CMaterialSystem* Interfaces::g_pMaterialSystem = nullptr;
	CLuaShared* Interfaces::g_pLuaShared = nullptr;

    CGlobalVars* Pointers::g_pCGlobalVars = nullptr;

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

	auto Pointers::GlobalVars() -> CGlobalVars* {
		// TODO: Update
		if ( !g_pCGlobalVars ) {
			CBasePattern pattern(
				"GlobalVars",
				GLOBALVARS_PATTERN,
				CLIENT_DLL
			);

			if ( !pattern.Search( false ) ) {
				LOG( "[error] GlobalVars: Pattern not found\n" );
				return nullptr;
			}

			const auto address = reinterpret_cast<uintptr_t>( pattern.GetFunction() );
			const auto offset = *reinterpret_cast<int32_t*>( address + 3 );
			g_pCGlobalVars = *reinterpret_cast<CGlobalVars**>( address + 7 + offset );
		}

		return g_pCGlobalVars;
	}

	auto Pointers::ViewMatrix() -> Matrix * {
		return &SDK::ViewMatrix;
	}
}