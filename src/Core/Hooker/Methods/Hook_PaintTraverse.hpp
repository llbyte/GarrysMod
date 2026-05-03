#pragma once

using PaintTraverse_t = void(__fastcall*)(
    void* thisptr,
    void* panel,
    bool forceRepaint,
    bool allowForce
);

auto Hook_PaintTraverse(
    void* thisptr,
    void* panel,
    bool forceRepaint,
    bool allowForce
) -> void;

inline PaintTraverse_t PaintTraverse_o = nullptr;
