#pragma once

#include <Common/Math/Vector.hpp>
#include <Common/Offsets.hpp>

class IClientRenderable {
protected:
    virtual ~IClientRenderable() = default;

public:

    Vector3& GetRenderOrigin( ) {
        return Call<Vector3&>( this, 1 );
    }

    Angle& GetRenderAngles( ) {
        return Call<Angle&>( this, 2 );
    }

    bool ShouldDraw( ) {
        return Call<bool>( this, 3 );
    }

    bool IsTransparent( ) {
        return Call<bool>( this, 4 );
    }

    void* GetModel( ) {
        return Call<void*>( this, 9 );
    }

    bool SetupBones( void* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime ) {
        return Call<bool>( this, 16, pBoneToWorldOut, nMaxBones, boneMask, currentTime );
    }

    void GetRenderBounds( Vector3& mins, Vector3& maxs ) {
        return Call<void>( this, 20, mins, maxs );
    }
};