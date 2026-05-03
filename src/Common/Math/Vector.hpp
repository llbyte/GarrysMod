#pragma once

#include <cmath>
#include <string>

#include "imgui.h"

namespace math {
    constexpr float PI = 3.14159265358979323846f;

    template<typename T>
    union vector3 {
        T data[3];
        struct {
            T x, y, z;
        };

        vector3 operator+(float in) const { return { this->x + in, this->y + in, this->z + in }; }
        vector3 operator+(vector3 in) const { return { this->x + in.x, this->y + in.y, this->z + in.z }; }
        vector3 operator-(float in) const { return { this->x - in, this->y - in, this->z - in }; }
        vector3 operator-(vector3 in) const { return { this->x - in.x, this->y - in.y, this->z - in.z }; }
        vector3 operator*(float in) const { return { this->x * in, this->y * in, this->z * in }; }
        vector3 operator*(vector3 in) const { return { this->x * in.x, this->y * in.y, this->z * in.z }; }
        vector3 operator/(float in) const { return { this->x / in, this->y / in, this->z / in }; }
        vector3 operator/(vector3 in) const { return { this->x / in.x, this->y / in.y, this->z / in.z }; }
        vector3& operator+=(float in) { this->x += in; this->y += in; this->z += in; return *this; }
        vector3& operator+=(vector3 in) { this->x += in.x; this->y += in.y; this->z += in.z; return *this; }
        vector3& operator-=(float in) { this->x -= in; this->y -= in; this->z -= in; return *this; }
        vector3& operator-=(vector3 in) { this->x -= in.x; this->y -= in.y; this->z -= in.z; return *this; }
        vector3& operator*=(float in) { this->x *= in; this->y *= in; this->z *= in; return *this; }
        vector3& operator*=(vector3 in) { this->x *= in.x; this->y *= in.y; this->z *= in.z; return *this; }
        vector3& operator/=(float in) { this->x /= in; this->y /= in; this->z /= in; return *this; }
        vector3& operator/=(vector3 in) { this->x /= in.x; this->y /= in.y; this->z /= in.z; return *this; }

        vector3& operator=(float in) {
            this->x = in;
            this->y = in;
            this->z = in;
            return *this;
        }

        bool operator==(const vector3& in) const { return this->x == in.x && this->y == in.y && this->z == in.z; }
        bool operator!=(const vector3& in) const { return !(*this == in); }

        vector3 ToAngle() const {
            return {
                std::atan2(-z, std::sqrt(x * x + y * y)) * (180.0f / PI),
                std::atan2(y, x) * (180.0f / PI),
                0.0f
            };
        }

        vector3 Normalize() const {
            vector3 out = *this;

            if (out.x > 89)
                out.x = 89;

            if (out.x < -89)
                out.x = -89;

            while (out.y > 180)
                out.y -= 360;

            while (out.y < -180)
                out.y += 360;

            out.z = 0;

            return out;
        }

        float Distance(const vector3& in) const {
            const float dx = in.x - x;
            const float dy = in.y - y;
            const float dz = in.z - z;
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }

        [[nodiscard]] bool Zero() const {
            return this->x == 0.f && this->y == 0.f && this->z == 0.f;
        }

        vector3 RelativeAngle() const {
            return {
                std::atan2(-z, std::hypot(x, y)) * (180.0f / PI),
                std::atan2(y, x) * (180.0f / PI),
                0.0f
            };
        }

        [[nodiscard]] bool invalid() const {
            return !x || !y || !z;
        }

        [[nodiscard]] std::string ToString() const {
            return std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z);
        }
    };

    template<typename T>
    union vector2 {
        T data[2];
        struct
        {
            T x, y;
        };

        vector2 operator+(float in) const { return { this->x + in, this->y + in }; }
        vector2 operator+(vector2 in) const { return { this->x + in.x, this->y + in.y }; }
        vector2 operator-(float in) const { return { this->x - in, this->y - in }; }
        vector2 operator-(vector2 in) const { return { this->x - in.x, this->y - in.y }; }
        vector2 operator*(float in) const { return { this->x * in, this->y * in }; }
        vector2 operator*(vector2 in) const { return { this->x * in.x, this->y * in.y }; }
        vector2 operator/(float in) const { return { this->x / in, this->y / in }; }
        vector2 operator/(vector2 in) const { return { this->x / in.x, this->y / in.y }; }
        vector2& operator+=(float in) { this->x += in; this->y += in; return *this; }
        vector2& operator+=(vector2 in) { this->x += in.x; this->y += in.y; return *this; }
        vector2& operator-=(float in) { this->x -= in; this->y -= in; return *this; }
        vector2& operator-=(vector2 in) { this->x -= in.x; this->y -= in.y; return *this; }
        vector2& operator*=(float in) { this->x *= in; this->y *= in; return *this; }
        vector2& operator*=(vector2 in) { this->x *= in.x; this->y *= in.y; return *this; }
        vector2& operator/=(float in) { this->x /= in; this->y /= in; return *this; }
        vector2& operator/=(vector2 in) { this->x /= in.x; this->y /= in.y; return *this; }

        bool operator==(const vector2& in) const { return this->x == in.x && this->y == in.y; }
        bool operator!=(const vector2& in) const { return !(*this == in); }

        [[nodiscard]] bool Invalid() const {
            return !x || !y;
        }

        [[nodiscard]] bool Zero() const {
            return this->x == 0.f && this->y == 0.f;
        }

        float Distance(const vector2& in) const {
            const float dx = in.x - x;
            const float dy = in.y - y;
            return std::sqrt(dx * dx + dy * dy);
        }

        [[nodiscard]] std::string ToString() const {
            return std::to_string(this->x) + ", " + std::to_string(this->y);
        }

        [[nodiscard]] ImVec2 ToImVec2() const {
            return ImVec2(this->x, this->y);
        }
    };

}

typedef math::vector2<float> Vector2;
typedef math::vector3<float> Vector3;
typedef math::vector3<float> Angle;