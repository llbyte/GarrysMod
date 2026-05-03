#pragma once

#include <d3d9.h>

using Present_t =
    HRESULT (WINAPI*)(
        IDirect3DDevice9*,
        const RECT*,
        const RECT*,
        HWND,
        const RGNDATA*
    );

auto Hook_Present(
    IDirect3DDevice9* pDevice,
    const RECT* pSourceRect,
    const RECT* pDestRect,
    HWND hDestWindowOverride,
    const RGNDATA* pDirtyRegion
) -> HRESULT;

inline Present_t Present_o = nullptr;