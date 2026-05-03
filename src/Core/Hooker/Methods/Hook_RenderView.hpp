#pragma once

#include <Core/SDK/Types/CViewSetup.hpp>

using RenderView_t = void(__fastcall*)(
    void* pViewRender,
    CViewSetup* view,
    int flags,
    int toDraw
);

auto Hook_RenderView(
    void* pViewRender,
    CViewSetup* view,
    int flags,
    int toDraw
) -> void;

inline RenderView_t RenderView_o = nullptr;