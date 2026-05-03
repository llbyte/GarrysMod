#include "Hook_OverrideView.hpp"

auto Hook_OverrideView(
    void* pClientMode,
    CViewSetup* pSetup
) -> int64_t {

    // pSetup->fov = 120.0;

    return OverrideView_o(pClientMode, pSetup);
}