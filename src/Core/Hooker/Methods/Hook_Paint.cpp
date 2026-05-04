#include "Hook_Paint.hpp"

#include <Core/SDK/SDK.hpp>

auto Hook_Paint(
    void* ecx,
    const int mode
) -> void {
    if (mode & 1 << 1) {
        SDK::Globals::g_pViewMatrix = SDK::Interfaces::EngineClient()->WorldToScreenMatrix();
    }

    return Paint_o(ecx, mode);
}
