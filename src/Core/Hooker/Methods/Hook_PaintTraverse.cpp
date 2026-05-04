#include "Hook_PaintTraverse.hpp"

auto Hook_PaintTraverse(
    void* thisptr,
    void* panel,
    const bool forceRepaint,
    const bool allowForce
) -> void {
    PaintTraverse_o(thisptr, panel, forceRepaint, allowForce);
}
