#pragma once

#include <Core/SDK/Types/C_BaseEntity.hpp>
#include <Core/SDK/Types/Base/IClientNetworkable.hpp>

#define CLIENT_ENTITYLIST_VERSION "VClientEntityList003"

class CClientEntityList {
protected:
    ~CClientEntityList() = default;

private:
    virtual void* GetClientNetworkable( int iIndex ) noexcept = 0;
    virtual void* GetClientNetworkableFromHandle( void* hEntity ) noexcept = 0;

    virtual void* GetClientUnknownFromHandle( void* hEntity ) noexcept = 0;

    virtual void* GetClientEntity( int iIndex ) noexcept = 0;
    virtual void* GetClientEntityFromHandle( void* hEntity ) noexcept = 0;

    virtual int NumberOfEntities( bool includeNonNetworkable ) noexcept = 0;
    virtual int GetHighestEntityIndex() noexcept = 0;
    virtual void SetMaxEntities( int maxEntities ) noexcept = 0;
    virtual int GetMaxEntities() noexcept = 0;

public:
    template<typename T = C_BaseEntity>
    auto GetBaseEntity( const int iIndex ) -> T* {
        return static_cast<T *>( GetClientEntity( iIndex ) );
    }

    template<typename T = IClientNetworkable>
    auto GetNetworkableEntity( const int iIndex ) -> T* {
        return static_cast<T *>( GetClientNetworkable( iIndex ) );
    }

    int GetHighestEntityList() noexcept {
        return GetHighestEntityIndex();
    }
};