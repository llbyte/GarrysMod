#include "CCheatMenu.hpp"

#include <imgui.h>
#include <algorithm>

#include <Core/SDK/SDK.hpp>
#include <Core/SDK/Math/Math.hpp>

static CCheatMenu g_CCheatMenu{};

namespace {
    struct ScreenBox {
        float left;
        float right;
        float top;
        float bottom;
    };

    auto BuildScreenBox( C_BaseEntity* entity, ScreenBox& out ) -> bool {
        auto* coll = entity->GetCollidable( );
        if ( !coll )
            return false;

        const Vector3 origin = entity->GetClientRenderable( )->GetRenderOrigin( );
        const Vector3 mins = coll->OBBMins( );
        const Vector3 maxs = coll->OBBMaxs( );

        const Vector3 points[8] = {
            { origin.x + mins.x, origin.y + mins.y, origin.z + mins.z },
            { origin.x + mins.x, origin.y + maxs.y, origin.z + mins.z },
            { origin.x + maxs.x, origin.y + maxs.y, origin.z + mins.z },
            { origin.x + maxs.x, origin.y + mins.y, origin.z + mins.z },
            { origin.x + maxs.x, origin.y + maxs.y, origin.z + maxs.z },
            { origin.x + mins.x, origin.y + maxs.y, origin.z + maxs.z },
            { origin.x + mins.x, origin.y + mins.y, origin.z + maxs.z },
            { origin.x + maxs.x, origin.y + mins.y, origin.z + maxs.z },
        };

        ImVec2 screen[8];
        for ( int k = 0; k < 8; ++k ) {
            if ( !Math::WorldToScreen( points[k], screen[k] ) )
                return false;
        }

        out.left = out.right = screen[0].x;
        out.top = out.bottom = screen[0].y;
        for ( int k = 1; k < 8; ++k ) {
            out.left = screen[k].x < out.left ? screen[k].x : out.left;
            out.right = screen[k].x > out.right ? screen[k].x : out.right;
            out.top = screen[k].y < out.top ? screen[k].y : out.top;
            out.bottom = screen[k].y > out.bottom ? screen[k].y : out.bottom;
        }

        return true;
    }

    auto DrawHpBar( const ScreenBox& box, const int health, const int maxHealth ) -> void {
        if ( maxHealth <= 0 )
            return;

        const float ratio = std::clamp( static_cast<float>( health ) / static_cast<float>( maxHealth ), 0.0f, 1.0f );
        constexpr float barWidth = 4.0f;
        constexpr float barPadding = 2.0f;
        const float barLeft = box.left - ( barWidth + barPadding );
        const float barRight = barLeft + barWidth;
        const float barTop = box.top;
        const float barBottom = box.bottom;
        const float barFillTop = barBottom - ( ( barBottom - barTop ) * ratio );

        auto* drawList = ImGui::GetBackgroundDrawList( );
        drawList->AddRectFilled( ImVec2( barLeft, barTop ), ImVec2( barRight, barBottom ), ImColor( 0, 0, 0, 160 ) );
        drawList->AddRectFilled( ImVec2( barLeft, barFillTop ), ImVec2( barRight, barBottom ), ImColor( 0, 255, 0, 220 ) );
        drawList->AddRect( ImVec2( barLeft, barTop ), ImVec2( barRight, barBottom ), ImColor( 0, 0, 0, 200 ) );
    }

    auto RenderEsp( ) -> void {
        const auto highest = SDK::Interfaces::ClientEntityList( )->GetHighestEntityList( );
        for ( int i = 0; i < highest; i++ ) {
            const auto pPlayer = SDK::Interfaces::ClientEntityList( )->GetBaseEntity( i );
            if ( !pPlayer )
                continue;

            if ( !pPlayer->IsPlayer( ) )
                continue;

            if ( pPlayer->GetHealth( ) <= 0 )
                continue;

            const auto pNetworkable = pPlayer->GetClientNetworkable( );
            if ( pNetworkable->IsDormant( ) )
                continue;

            ScreenBox box{};
            if ( !BuildScreenBox( pPlayer, box ) )
                continue;

            ImGui::GetBackgroundDrawList( )->AddRect(
                ImVec2( box.left, box.top ),
                ImVec2( box.right, box.bottom ),
                ImColor( 255, 0, 0 ),
                0.0f,
                0,
                1.0f
            );

            DrawHpBar( box, pPlayer->GetHealth( ), pPlayer->GetMaxHealth( ) );
        }
    }
}

auto CCheatMenu::OnRenderMenu() -> void {
    ImGui::Begin("Garry's Mod Menu");
    ImGui::Text("ImGui DX9 OK");
    ImGui::End();

    RenderEsp( );

}

auto GetCheatMenu() -> CCheatMenu* {
	return &g_CCheatMenu;
}