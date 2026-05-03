#include "Hook_Paint.hpp"

#include <cstring>

#include "Common/Log/CLog.hpp"
#include "Core/SDK/SDK.hpp"

auto Hook_Paint(
    void* ecx,
    const int mode
) -> void {
    constexpr int PAINT_INGAMEPANELS = (1 << 1);
    if (mode & PAINT_INGAMEPANELS) {
        SDK::ViewMatrix = SDK::Interfaces::EngineClient()->WorldToScreenMatrix();
    }

    return Paint_o(ecx, mode);
}
