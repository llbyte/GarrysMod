#pragma once

#include "C_BaseEntity.hpp"

class C_BaseCombatWeapon {
public:

    const char* GetName( ) {
        return Call<const char*>( this, 368 );
    }

    const char* GetPrintName( ) {
        return Call<const char*>( this,  369 );
    }

};
