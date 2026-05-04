#pragma once

#include <Core/SDK/Update/CModelRender.hpp>
#include <Common/Math/Vector.hpp>

struct ModelRenderInfo_t {
	Vector3 origin;
	Angle angles;
	void* pRenderable;
	const void* pModel;
	const void* pModelToWorld;
	const void* pLightingOffset;
	const Vector3* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitbox_set;
	void* instance;
};

struct DrawModelState_t;

using DrawModelExecute_t = void(__fastcall*)(
    CModelRender* model_render,
    const DrawModelState_t& state,
    const ModelRenderInfo_t& info,
    void* pCustomBoneToWorld
);

auto Hook_DrawModelExecute(
    CModelRender* model_render,
    const DrawModelState_t& state,
    const ModelRenderInfo_t& info,
    void* pCustomBoneToWorld
) -> void;

inline DrawModelExecute_t DrawModelExecute_o = nullptr;
