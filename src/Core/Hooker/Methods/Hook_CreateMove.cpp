#include "Hook_CreateMove.hpp"

auto Hook_CreateMove(
    __int64 a1,
    const float flInputSampleTime,
    CUserCmd* cmd
) -> __int64 {

    const auto result = CreateMove_o(a1, flInputSampleTime, cmd);
    if (!cmd || !cmd->command_number)
        return result;

    cmd->buttons &= ~CUserCmd::IN_JUMP;

    return result;
}
