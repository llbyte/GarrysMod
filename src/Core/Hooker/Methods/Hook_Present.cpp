#include "Hook_Present.hpp"

#include <Core/Menu/CMenuRender.hpp>

auto Hook_Present(
    IDirect3DDevice9* pDevice,
    const RECT* pSourceRect,
    const RECT* pDestRect,
    HWND hDestWindowOverride,
    const RGNDATA* pDirtyRegion
) -> HRESULT {

    GetMenuRender()->OnPresent(
        pDevice,
        pSourceRect,
        pDestRect,
        hDestWindowOverride,
        pDirtyRegion
    );

    return Present_o(
        pDevice,
        pSourceRect,
        pDestRect,
        hDestWindowOverride,
        pDirtyRegion
    );
}