#include "CCheatMenu.hpp"

#include <imgui.h>

#include "Core/SDK/SDK.hpp"
#include "Core/SDK/Types/C_BaseEntity.hpp"

static CCheatMenu g_CCheatMenu{};

bool WorldToScreen(const Vector3& WorldPos, Vector2& ScreenPos, const Matrix& Matrix) {
    float w = Matrix[3][0] * WorldPos.x + Matrix[3][1] * WorldPos.y + Matrix[3][2] * WorldPos.z + Matrix[3][3];

    if (w < 0.001f) {
        return false;
    }

    const float inv_w = 1.0f / w;

    const float ndc_x = (Matrix[0][0] * WorldPos.x + Matrix[0][1] * WorldPos.y + Matrix[0][2] * WorldPos.z + Matrix[0][3]) * inv_w;
    const float ndc_y = (Matrix[1][0] * WorldPos.x + Matrix[1][1] * WorldPos.y + Matrix[1][2] * WorldPos.z + Matrix[1][3]) * inv_w;

    int width, height;
    SDK::Interfaces::EngineClient()->GetScreenSize(width, height);
    const auto w_f = static_cast<float>(width);
    const auto h_f = static_cast<float>(height);

    const float screen_x = (w_f * 0.5f) + (ndc_x * w_f * 0.5f);
    const float screen_y = (h_f * 0.5f) - (ndc_y * h_f * 0.5f);

    ScreenPos.x = screen_x;
    ScreenPos.y = screen_y;

    return true;
}

auto m_bEsp = false;

auto CCheatMenu::OnRenderMenu() -> void {
    ImGui::Begin("Garry's Mod Menu");
    ImGui::Text("ImGui DX9 OK");
    ImGui::Checkbox("ESP", &m_bEsp);
    ImGui::End();




    const auto highest = SDK::Interfaces::ClientEntityList()->GetHighestEntityList();
    for (int i = 0; i < highest; i++) {
        // if (i == localPlayerIndex) continue;

        const auto pPlayer = SDK::Interfaces::ClientEntityList()->GetBaseEntity(i);
        if (!pPlayer)
            continue;

        if (!pPlayer->IsPlayer())
            continue;

        auto pNetworkable = pPlayer->GetClientNetworkable();
        if (pNetworkable->IsDormant())
            continue;

        auto* coll = pPlayer->GetCollidable();
        if (!coll)
            continue;

        auto* rend = pPlayer->GetClientRenderable();
        if (!rend)
            continue;

        const Vector3 origin = rend->GetRenderOrigin();
        Vector3 mins, maxs;
        rend->GetRenderBounds(mins, maxs);

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

        Vector2 screen[8];
        bool ok = true;
        for (int k = 0; k < 8; ++k) {
            if (!WorldToScreen(points[k], screen[k], SDK::ViewMatrix)) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;

        float left = screen[0].x, right = screen[0].x;
        float top = screen[0].y, bottom = screen[0].y;
        for (int k = 1; k < 8; ++k) {
            left = (screen[k].x < left) ? screen[k].x : left;
            right = (screen[k].x > right) ? screen[k].x : right;
            top = (screen[k].y < top) ? screen[k].y : top;
            bottom = (screen[k].y > bottom) ? screen[k].y : bottom;
        }

        // const auto gun_handle = pPlayer->GetActiveWeaponHandle();
        // const auto gun = SDK::Interfaces::ClientEntityList()->GetBaseEntityFromHandle<C_BaseCombatWeapon>(gun_handle);
        // const auto object_type = gun->GetClientNetworkable()->GetClientClass()->m_pNetworkName();

        ImGui::GetBackgroundDrawList()->AddRect(
            ImVec2(left, top),
            ImVec2(right, bottom),
            ImColor(255, 0, 0),
            0.0f,
            0,
            1.0f
        );

        // ImGui::GetBackgroundDrawList()->AddText(
        //     ImVec2(left - 15, top),
        //     ImColor(255, 255, 255),
        //     object_type
        // );
    }
}

auto GetCheatMenu() -> CCheatMenu* {
	return &g_CCheatMenu;
}