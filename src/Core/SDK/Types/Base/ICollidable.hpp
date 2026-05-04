#pragma once

#include <Common/Math/Vector.hpp>

class ICollidable {
protected:
    virtual ~ICollidable() = default;

public:

    Vector3& OBBMins( ) {
        return Call<Vector3&>( this, 3 );
    }
    Vector3& OBBMaxs( ) {
        return Call<Vector3&>( this, 4 );
    }

};
