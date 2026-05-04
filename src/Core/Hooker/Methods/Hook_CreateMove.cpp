#include "Hook_CreateMove.hpp"

#include "Common/Log/CLog.hpp"

auto Hook_CreateMove(
    const uintptr_t ClientMode,
    const float flInputSampleTime,
    CUserCmd* cmd
) -> bool {

    const auto result = CreateMove_o(ClientMode, flInputSampleTime, cmd);
    // if ( !cmd || !cmd->commandNumber )
    //     return result;

    // Use spawm
    // if(cmd->commandNumber % 2)
    //     cmd->buttonFlags |= static_cast<int>(CUserCmd::ButtonFlag::Use);
    // else cmd->buttonFlags &= ~static_cast<int>(CUserCmd::ButtonFlag::Use);

    return result;
}
