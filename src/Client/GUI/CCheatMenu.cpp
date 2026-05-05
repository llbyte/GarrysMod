#include "CCheatMenu.hpp"

#include <imgui.h>

static CCheatMenu g_CCheatMenu{};

auto CCheatMenu::OnRenderMenu() -> void {
    static bool open = true;

    ImGui::SetNextWindowSize(ImVec2(850, 550), ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 8.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.09f, 0.11f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.16f, 0.17f, 0.20f, 1.0f));

    ImGui::Begin("f", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::End();
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(4);
}

auto GetCheatMenu() -> CCheatMenu* {
	return &g_CCheatMenu;
}