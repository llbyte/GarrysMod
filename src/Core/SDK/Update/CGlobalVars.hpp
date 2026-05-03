#pragma once

#include <Common/Offsets.hpp>

#define GLOBALVARS_PATTERN "48 8B 05 ? ? ? ? 83 78 14 01 75 09"

class CGlobalVars {
    ~CGlobalVars() = default;

    OFFSET( float, 0x00, m_fRealTime )
    OFFSET( int, 0x0C, m_fCurrentTime )
    OFFSET( int, 0x14, m_iMaxClients )
    OFFSET( float, 0x1C, m_fIntervalPerTick )
    OFFSET( float, 0x20, m_fInterpolationAmount )


public:
    auto GetTickrate() noexcept -> float {
        return 1.0f / m_fIntervalPerTick();
    }

    auto GetMaxClients() noexcept -> int {
        return m_iMaxClients();
    }
};