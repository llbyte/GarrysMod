#pragma once

#include <Core/SDK/Update/CUserCmd.hpp>

using CreateMove_t = bool(__fastcall*)(
    uintptr_t ClientMode,
    float flInputSampleTime,
    CUserCmd* cmd
);

auto Hook_CreateMove(
    uintptr_t ClientMode,
    float flInputSampleTime,
    CUserCmd* cmd
) -> bool;

inline CreateMove_t CreateMove_o = nullptr;