#include "CCheatMenu.hpp"

#include <imgui.h>

static CCheatMenu g_CCheatMenu{};


auto CCheatMenu::OnRenderMenu() -> void {
    auto test = false;

    ImGui::SetNextWindowSize(ImVec2(840, 575), ImGuiCond_Always);
    ImGui::Begin("f", &test, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::End();

}

auto GetCheatMenu() -> CCheatMenu* {
	return &g_CCheatMenu;
}