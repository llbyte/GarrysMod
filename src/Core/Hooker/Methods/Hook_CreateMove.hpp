#pragma once

#include <Core/SDK/Update/CUserCmd.hpp>

// C_BasePlayer
// pattern 48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? BA ? ? ? ? 48 8B CB - spawn
// 48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC ? 48 8B DA - InitialSpawn ?
// 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 41 8B F1 49 8B E8 48 8B DA - hud?

// IClientMode
// 40 53 48 83 EC ? 0F 29 74 24 ? 49 8B D8 - createmove?

using CreateMove_t = __int64(__fastcall*)(
    __int64 a1,
    float flInputSampleTime,
    CUserCmd* cmd
);

auto Hook_CreateMove(
    __int64 a1,
    float flInputSampleTime,
    CUserCmd* cmd
) -> __int64;

inline CreateMove_t CreateMove_o = nullptr;