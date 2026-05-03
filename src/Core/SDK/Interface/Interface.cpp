#include "Interface.hpp"

#include <Windows.h>

CreateInterfaceFn CaptureFactory( const char* FactoryModule ) {
    CreateInterfaceFn Interface = nullptr;

    if (const HMODULE hFactoryModule = GetModuleHandleA( FactoryModule ) )
        Interface = reinterpret_cast<CreateInterfaceFn>( GetProcAddress( hFactoryModule, "CreateInterface" ) );

    return Interface;
}