#pragma once

#include <Common/Offsets.hpp>
#include <Core/SDK/Types/ClientClass.hpp>

class IClientNetworkable {
protected:
    virtual ~IClientNetworkable() = default;

public:

    ClientClass* GetClientClass( ) {
        return Call<ClientClass*>( this, 2);
    }

    bool IsDormant( ) {
        return Call<bool>( this, 8 );
    }

    int EntIndex( ) {
        return Call<int>( this, 9 );
    }

};
