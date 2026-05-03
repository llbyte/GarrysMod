#include "CBasePattern.hpp"

#include "Common/Log/CLog.hpp"

CBasePattern::CBasePattern(
    const char* szPatternName,
    const char* szPattern,
    const char* szDll,
    const uint32_t Offset,
    const PatternSearchType Type
) {
    PatternName = szPatternName;
    Pattern = szPattern;
    Dll = szDll;
    dwOffset = Offset;
    m_Type = Type;
}

auto CBasePattern::Search( const bool SkipError ) -> bool {
    if ( m_Type != SEARCH_TYPE_PROC ) {
        const uintptr_t address = FindPattern( Dll, Pattern, dwOffset );

        if ( !address ) {
            if ( !SkipError )
                LOG( "[error] CBasePattern: %s\n" , PatternName );

            return false;
        }

        pFunction = reinterpret_cast<PVOID>( address );
    }

    if ( m_Type == SEARCH_TYPE_PTR )
        pFunction = reinterpret_cast<PVOID>( *static_cast<uintptr_t*>( pFunction ) );

    return true;
}

auto CBasePattern::GetPatternName() -> const char* {
    return PatternName;
}

auto CBasePattern::GetDllName() -> const char* {
    return Dll;
}

auto CBasePattern::GetFunction() -> PVOID {
    return pFunction;
}