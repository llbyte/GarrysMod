#pragma once

#include <Common/Offsets.hpp>
#include <Core/SDK/Types/Base/IClientNetworkable.hpp>
#include <Core/SDK/Types/Base/ICollidable.hpp>
#include <Core/SDK/Types/Base/IClientRenderable.hpp>

class C_BaseEntity {
protected:
    virtual ~C_BaseEntity() = default;

public:

    ICollidable* GetCollidable( ) {
        return Call<ICollidable*>( this, 3);
    }

    IClientNetworkable* GetClientNetworkable( ) {
        return Call<IClientNetworkable*>( this, 4);
    }

    IClientRenderable* GetClientRenderable( ) {
        return Call<IClientRenderable*>( this, 5);
    }

    int GetHealth( ) {
        return Call<int>( this, 109 );
    }

    int GetMaxHealth( ) {
        return Call<int>( this, 110 );
    }

    bool IsPlayer( ) {
        return Call<bool>( this, 131 );
    }

    bool IsNPC( ) {
        return Call<bool>( this, 134 );
    }

    bool IsARagdoll( ) {
        return Call<bool>( this, 159 );
    }

    bool IsWeapon( ) {
        return Call<bool>( this, 168 );
    }

    bool IsVehicle( ) {
        return Call<bool>( this, 169 );
    }

    void PushEntity( ) {
        return Call<void>( this, 173 );
    }

};
