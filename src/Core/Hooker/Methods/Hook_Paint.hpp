#pragma once

using Paint_t = void(__thiscall*)(
    void* ecx,
    int mode
);

auto Hook_Paint(
    void* ecx,
    int mode
) -> void;

inline Paint_t Paint_o = nullptr;