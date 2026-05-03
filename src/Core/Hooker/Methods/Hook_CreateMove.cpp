#include "Hook_CreateMove.hpp"

auto Hook_CreateMove(
    __int64 a1,
    __int64 a2,
    __int64 a3
) -> __int64 {

    // LOG("[hook] CreateMove hook called! \n");

    return CreateMove_o(a1, a2, a3);
}
