#include "Math.hpp"
#include <Core/SDK/SDK.hpp>

namespace Math {

    namespace {
        auto ScreenTransform( const Vector3& vIn , Vector3& vOut ) -> bool {
            const Matrix& view = *SDK::Globals::ViewMatrix();

            const float w = view[ 3 ][ 0 ] * vIn.x + view[ 3 ][ 1 ] * vIn.y + view[ 3 ][ 2 ] * vIn.z + view[ 3 ][ 3 ];
            if ( w < 0.001f ) {
                vOut = { 0.0f, 0.0f, 0.0f };
                return false;
            }

            const float x = view[ 0 ][ 0 ] * vIn.x + view[ 0 ][ 1 ] * vIn.y + view[ 0 ][ 2 ] * vIn.z + view[ 0 ][ 3 ];
            const float y = view[ 1 ][ 0 ] * vIn.x + view[ 1 ][ 1 ] * vIn.y + view[ 1 ][ 2 ] * vIn.z + view[ 1 ][ 3 ];
            const float z = view[ 2 ][ 0 ] * vIn.x + view[ 2 ][ 1 ] * vIn.y + view[ 2 ][ 2 ] * vIn.z + view[ 2 ][ 3 ];

            vOut.x = x / w;
            vOut.y = y / w;
            vOut.z = z / w;

            return true;
        }
    }

    auto WorldToScreen( const Vector3& vIn , ImVec2& vOut ) -> bool {
        Vector3 out;

        if ( !ScreenTransform( vIn , out ) ) {
            return false;
        }

        const ImVec2 display = ImGui::GetIO().DisplaySize;
        vOut.x = ( out.x + 1.0f ) * 0.5f * display.x;
        vOut.y = display.y - ( out.y + 1.0f ) * 0.5f * display.y;

        return true;
    }

    auto WorldToScreen( const Vector3& vIn , Vector2& vOut ) -> bool {
        Vector3 out;    

        if ( !ScreenTransform( vIn , out ) ) {
            return false;
        }

        const ImVec2 display = ImGui::GetIO().DisplaySize;
        vOut.x = ( out.x + 1.0f ) * 0.5f * display.x;
        vOut.y = display.y - ( out.y + 1.0f ) * 0.5f * display.y;

        return true;
    }

}