#include "CCheatMenu.hpp"

#include <imgui.h>

static CCheatMenu g_CCheatMenu{};

auto m_bEsp = false;

auto CCheatMenu::OnRenderMenu() -> void {
    ImGui::Begin("Garry's Mod Menu");
    ImGui::Text("ImGui DX9 OK");
    ImGui::Checkbox("ESP", &m_bEsp);
    ImGui::End();

}

auto GetCheatMenu() -> CCheatMenu* {
	return &g_CCheatMenu;
}