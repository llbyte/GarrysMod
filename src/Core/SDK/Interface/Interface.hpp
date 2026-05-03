#pragma once

typedef void* ( *CreateInterfaceFn )( const char* pName, int* pReturnCode );

CreateInterfaceFn CaptureFactory( const char* FactoryModule );

template<typename T>
T* CaptureInterface(const CreateInterfaceFn Interface, const char* InterfaceName ) {
    T* dwPointer = static_cast<T *>( Interface( InterfaceName, nullptr ) );
    return dwPointer;
}