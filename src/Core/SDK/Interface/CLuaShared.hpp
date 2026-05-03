#pragma once

#include <string>
#include <Common/Math/Vector.hpp>
#include <Common/Offsets.hpp>

#define LUA_SHARED_VERSION "LUASHARED003"

enum LuaInterfaceType {
    CLIENT = 0,
    SERVER = 1,
    MENU = 2
};

enum class ObjectType : int {
    Invalid = -1,
    Nil = 0,
    Boolean,
    LightUserData,
    Number,
    String,
    Table,
    Function,
    UserData,
    Thread,
    Entity,
    Vector,
    Angle,
    PhysObj,
    Save,
    Restore,
    DamageInfo,
    EffectData,
    MoveData,
    RecipientFilter,
    UserCmd,
    ScriptedVehicle,
    Material,
    Panel,
    Particle,
    ParticleEmitter,
    Texture,
    IMesh,
    Matrix,
    PixelVisHandle,
    DLight,
    Video,
    UserMsg,
    ConVar,
    Sound,
    File,
    Count
};

class CLuaInterface {
protected:
    ~CLuaInterface() = default;

public:
    virtual int Top() = 0;
    virtual void* Push( int iStackPos ) = 0;
    virtual void* Pop( int iAmt = 1 ) = 0;
    virtual void* GetTable( int iStackPos ) = 0;
    virtual void* const GetField( int iStackPos, const char* ) = 0;
    virtual void SetField( int iStackPos, const char* ) = 0;
    virtual void* CreateTable() = 0;
    virtual void* SetTable( int ) = 0;
    virtual void* SetMetaTable( int ) = 0;
    virtual void* GetMetaTable( int ) = 0;
    virtual void* Call( int iArgs, int iRets ) = 0;
    virtual void* PCall( int, int, int ) = 0;
    virtual void* Equal( int, int ) = 0;
    virtual void* RawEqual( int, int ) = 0;
    virtual void* Insert( int ) = 0;
    virtual void* Remove( int ) = 0;
    virtual void* Next( int ) = 0;
    virtual void* NewUserdata( unsigned int ) = 0;
    virtual void* ThrowError( const char* ) = 0;
    virtual void* CheckType( int, int ) = 0;
    virtual void* ArgError( int, const char* ) = 0;
    virtual void* RawGet( int iStackPos ) = 0;
    virtual void* RawSet( int iStackPos ) = 0;
    virtual const char* GetString( int iStackPos = -1, unsigned int* iOutLen = nullptr ) = 0;
    virtual double GetNumber( int iStackPos = -1 ) = 0;
    virtual bool GetBool( int iStackPos = -1 ) = 0;
    virtual void* GetCFunction( int iStackPos = -1 ) = 0;
    virtual void* GetUserdata( int iStackPos = -1 ) = 0;
    virtual void PushNil() = 0;
    virtual void PushString( const char*, unsigned int iLen = 0 ) = 0;
    virtual void PushNumber( double ) = 0;
    virtual void PushBool( bool ) = 0;
    virtual void PushCFunction( int ( * )( void* ) ) = 0;
    virtual void PushCClosure( int ( * )( void* ), int ) = 0;
    virtual void PushUserdata( void* ) = 0;
    virtual void* ReferenceCreate() = 0;
    virtual void* ReferenceFree( int ) = 0;
    virtual void* ReferencePush( int ) = 0;
    virtual void* PushSpecial( int ) = 0;
    virtual bool IsType( int, ObjectType ) = 0;
    virtual void* GetType( int ) = 0;
    virtual void* GetTypeName( int ) = 0;
    virtual void* CreateMetaTableType( const char*, int ) = 0;
    virtual void* CheckString( int ) = 0;
    virtual void* CheckNumber( int ) = 0;
    virtual void* ObjLen( int ) = 0;
    virtual void* GetAngle( int ) = 0;
    virtual void* GetVector( int ) = 0;
    virtual void* PushAngle( const Angle& ) = 0;
    virtual void* PushVector( const Vector3& ) = 0;
    virtual void* SetState( void* ) = 0;
    virtual void* CreateMetaTable( const char* ) = 0;
    virtual void* PushMetaTable( int ) = 0;
    virtual void* PushUserType( void*, int ) = 0;
    virtual void* SetUserType( int, void* ) = 0;
    virtual void* Init( void*, bool ) = 0;
    virtual void* Shutdown() = 0;
    virtual void* Cycle() = 0;
    virtual void* Global() = 0;
    virtual void* GetObject( int ) = 0;
    virtual void* PushLuaObject( void* ) = 0;
    virtual void* PushLuaFunction( int ( * )( void* ) ) = 0;
    virtual void* LuaError( const char*, int ) = 0;
    virtual void* TypeError( const char*, int ) = 0;
    virtual void* CallInternal( int, int ) = 0;
    virtual void* CallInternalNoReturns( int ) = 0;
    virtual void* CallInternalGetBool( int ) = 0;
    virtual void* CallInternalGetString( int ) = 0;
    virtual void* CallInternalGet( int, void* ) = 0;
    virtual void* NewGlobalTable( const char* ) = 0;
    virtual void* NewTemporaryObject() = 0;
    virtual bool IsUserData( int ) = 0;
    virtual void* GetMetaTableObject( const char*, int ) = 0;
    virtual void* GetMetaTableObject( int ) = 0;
    virtual void* GetReturn( int ) = 0;
    virtual bool IsServer() = 0;
    virtual bool IsClient() = 0;
    virtual bool IsMenu() = 0;
    virtual void* DestroyObject( void* ) = 0;
    virtual void* CreateObject() = 0;
    virtual void* SetMember( void*, void*, void* ) = 0;
    virtual void* GetNewTable() = 0;
    virtual void* SetMember( void*, float ) = 0;
    virtual void* SetMember( void*, float, void* ) = 0;
    virtual void* SetMember( void*, const char* ) = 0;
    virtual void* SetMember( void*, const char*, void* ) = 0;
    virtual void* SetType( unsigned char ) = 0;
    virtual void* PushLong( long ) = 0;
    virtual void* GetFlags( int ) = 0;
    virtual void* FindOnObjectsMetaTable( int, int ) = 0;
    virtual void* FindObjectOnTable( int, int ) = 0;
    virtual void* SetMemberFast( void*, int, int ) = 0;
    virtual void* RunString( const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors ) = 0;
    virtual bool IsEqual( void*, void* ) = 0;
    virtual void* Error( const char* ) = 0;
    virtual void* GetStringOrError( int ) = 0;
    virtual void* RunLuaModule( const char* ) = 0;
    virtual void* FindAndRunScript( const char*, bool, bool, const char*, bool ) = 0;
    virtual void* SetPathID( const char* ) = 0;
    virtual const char* GetPathID() = 0;
    virtual void* ErrorNoHalt( const char*, ... ) = 0;
    virtual void* Msg( const char*, ... ) = 0;
    virtual void* PushPath( const char* ) = 0;
    virtual void* PopPath() = 0;
    virtual const char* GetPath() = 0;
    virtual void* GetColor( int ) = 0;
    virtual void* PushColor( void* ) = 0;
    virtual void* GetStack( int, void* ) = 0;
    virtual void* GetInfo( const char*, void* ) = 0;
    virtual void* GetLocal( void*, int ) = 0;
    virtual void* GetUpvalue( int, int ) = 0;
    virtual void* RunStringEx( const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns ) = 0;
    virtual void* GetDataString( int, void** ) = 0;
    virtual void* ErrorFromLua( const char*, ... ) = 0;
    virtual void* GetCurrentLocation() = 0;
    virtual void* MsgColour( const int&, const char*, ... ) = 0;
    virtual void* GetCurrentFile( std::string, std::string ) = 0;
    virtual void* CompileString( void*, const std::string& ) = 0;
    virtual void* CallFunctionProtected( int, int, bool ) = 0;
    virtual void* Require( const char* ) = 0;
    virtual void* GetActualTypeName( int ) = 0;
    virtual void* PreCreateTable( int, int ) = 0;
    virtual void* PushPooledString( int ) = 0;
    virtual void* GetPooledString( int ) = 0;
    virtual void* AddThreadedCall( void* ) = 0;
    virtual void* AppendStackTrace( char*, unsigned long ) = 0;
    virtual void* CreateConVar( const char* name, const char* description, const char* value, int ) = 0;
    virtual void* CreateConCommand( const char*, const char*, int, void ( * )( const void* ), int ( * )( const char*, char ( * )[128] ) ) = 0;
};

class CLuaShared {
protected:
    ~CLuaShared() = default;

public:

    void* DumpStats( ) {
        return Call<void*>( this, 3 );
    }

    void* GetStackTraces( void* ) {
        return Call<void*>( this, 15 );
    }

    /*
        __int64 __fastcall GetLuaInterface(__int64 a1, unsigned __int8 a2) {
            return *(_QWORD *)(a1 + 8LL * a2 + 120);
        }
     */
    CLuaInterface* GetLuaInterface( const LuaInterfaceType type ) {
        const auto base = reinterpret_cast<uintptr_t>( this );
        return *reinterpret_cast<CLuaInterface**>( base + 120 + 8LL * type );
    }

};