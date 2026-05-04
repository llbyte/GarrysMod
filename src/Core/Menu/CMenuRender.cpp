#include "CMenuRender.hpp"

#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>

#include <Client/GUI/CCheatMenu.hpp>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
);

static CMenuRender g_Menu{};

auto CMenuRender::Init( IDirect3DDevice9* device ) -> void {
    if ( !device || m_bInit )
        return;

    m_pDevice = device;

    D3DDEVICE_CREATION_PARAMETERS params{};
    device->GetCreationParameters(&params);
    m_hWindow = params.hFocusWindow;

    IMGUI_CHECKVERSION();
    m_pImGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext( m_pImGuiContext );

    ImGui_ImplWin32_Init( m_hWindow);
    ImGui_ImplDX9_Init( m_pDevice );

    m_WndProcOrig = reinterpret_cast<WNDPROC>(SetWindowLongPtr(
        m_hWindow,
        GWLP_WNDPROC,
        reinterpret_cast<LONG_PTR>(MenuWndProc)
    ));

    m_bInit = true;
}

auto CMenuRender::Destroy() -> void {
    if ( !m_bInit )
        return;

    if ( m_WndProcOrig && m_hWindow ) {
        SetWindowLongPtr(
            m_hWindow,
            GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(m_WndProcOrig)
        );
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext( m_pImGuiContext );

    m_pImGuiContext = nullptr;

    m_pDevice = nullptr;
    m_bInit = false;
    m_bVisible = false;
}

auto CMenuRender::OnPresent(
    IDirect3DDevice9* pDevice,
    const RECT* pSourceRect,
    const RECT* pDestRect,
    HWND hDestWindowOverride,
    const RGNDATA* pDirtyRegion
) -> void {
    if ( !m_bInit ) {
        Init( pDevice );
        return;
    }

    // patch start
    ImGui::SetCurrentContext( m_pImGuiContext );
    auto& io = ImGui::GetIO();
    if ( !m_bVisible ) {
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        return;
    }
    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
    // patchend

    IDirect3DStateBlock9* state = nullptr;
    pDevice->CreateStateBlock(D3DSBT_ALL, &state);
    state->Capture();

    pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);

    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    if ( m_bVisible ) {
        GetCheatMenu()->OnRenderMenu();
    }

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    state->Apply();
    state->Release();
}

LRESULT WINAPI CMenuRender::MenuWndProc(
    HWND hwnd,
    const UINT uMsg,
    const WPARAM wParam,
    const LPARAM lParam
) {
    // patch start
    if ( g_Menu.m_bVisible ) {
        ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
    }
    // patch end

    if (uMsg == WM_KEYUP && wParam == VK_INSERT)
        g_Menu.m_bVisible = !g_Menu.m_bVisible;

    return CallWindowProc(
        g_Menu.m_WndProcOrig,
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

auto GetMenuRender() -> CMenuRender* {
    return &g_Menu;
}