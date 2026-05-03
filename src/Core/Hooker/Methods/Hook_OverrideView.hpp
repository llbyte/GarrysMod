#pragma once

#include <Core/SDK/Types/CViewSetup.hpp>

using OverrideView_t = int64_t(__fastcall*)(
    void* pClientMode,
    CViewSetup* pSetup
);

auto Hook_OverrideView(
    void* pClientMode,
    CViewSetup* pSetup
) -> int64_t;

inline OverrideView_t OverrideView_o = nullptr;