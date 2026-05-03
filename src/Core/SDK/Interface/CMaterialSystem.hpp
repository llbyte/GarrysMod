#pragma once

#include <Core/SDK/Update/IMaterial.hpp>
#include <Common/Offsets.hpp>

#define MATERIAL_SYSTEM_VERSION "VMaterialSystem080"

class CMaterialSystem {
protected:
    ~CMaterialSystem() = default;

public:

    IMaterial* FindMaterial(
        const char* pMaterialName,
        const char* pTextureGroupName,
        bool complain = true,
        const char* pComplainPrefix = nullptr
    ) {
        using Fn = IMaterial*( __fastcall* )( void*, const char*, const char*, bool, const char* );

        return Call<Fn>( this, 75, pMaterialName, pTextureGroupName, complain, pComplainPrefix );
    }
};
