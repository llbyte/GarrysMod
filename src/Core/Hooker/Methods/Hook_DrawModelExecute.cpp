#include "Hook_DrawModelExecute.hpp"

auto Hook_DrawModelExecute(
    CModelRender* model_render,
    const DrawModelState_t& state,
    const ModelRenderInfo_t& info,
    void* pCustomBoneToWorld
) -> void {
    return DrawModelExecute_o(model_render, state, info, pCustomBoneToWorld);
}
