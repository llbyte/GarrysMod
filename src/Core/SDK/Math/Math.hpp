#pragma once

#include <Common/Math/Vector.hpp>

namespace Math {

    auto WorldToScreen( const Vector3& vIn , ImVec2& vOut ) -> bool;
    auto WorldToScreen( const Vector3& vIn , Vector2& vOut ) -> bool;

}
