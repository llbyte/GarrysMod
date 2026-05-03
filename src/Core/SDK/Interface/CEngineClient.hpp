#pragma once

#include <Common/Offsets.hpp>

#define ENGINE_CLIENT_VERSION "VEngineClient015"

class CEngineClient {
protected:
    ~CEngineClient() = default;

public:
    void GetScreenSize( int& width, int& height ) {
        return Call<void>( this, 5, width, height );
    }

    int GetLocalPlayer( ) {
        return Call<int>( this, 12 );
    }
    int GetMaxClients( ) {
        return Call<int>( this, 21 );
    }

    bool IsInGame( ) {
        return Call<bool>( this, 26 );
    }
    bool IsConnected( ) {
        return Call<bool>( this, 27 );
    }

    Matrix& WorldToScreenMatrix( ) {
        return Call<Matrix&>( this, 36 );
    }
    Matrix& WorldToViewMatrix( ) {
        return Call<Matrix&>( this, 37 );
    }

    const char* GetGameDirectory( ) {
        return Call<const char*>( this, 35 );
    }
};
