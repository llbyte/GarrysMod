#pragma once

#include <d3d9.h>
#include <imgui.h>

class ICheatMenuRender {
public:
    virtual ~ICheatMenuRender() = default;

    virtual bool IsVisible() = 0;
    virtual bool IsInited() = 0;

    virtual auto OnPresent(
        IDirect3DDevice9* pDevice,
        const RECT* pSourceRect,
        const RECT* pDestRect,
        HWND hDestWindowOverride,
        const RGNDATA* pDirtyRegion
    ) -> void = 0;
};

class CMenuRender final : public ICheatMenuRender {
public:
    void Init( IDirect3DDevice9* device );
    void Destroy();

    auto OnPresent(
        IDirect3DDevice9* pDevice,
        const RECT* pSourceRect,
        const RECT* pDestRect,
        HWND hDestWindowOverride,
        const RGNDATA* pDirtyRegion
    ) -> void override;

    bool IsVisible() override { return m_bVisible; }
    bool IsInited() override { return m_bInit; }

    static LRESULT WINAPI MenuWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    [[nodiscard]] auto GetDevice() const -> IDirect3DDevice9* { return m_pDevice; }

private:
    IDirect3DDevice9* m_pDevice = nullptr;

    ImGuiContext* m_pImGuiContext = nullptr;
    WNDPROC m_WndProcOrig = nullptr;

    HWND m_hWindow = nullptr;
    bool m_bInit = false;
    bool m_bVisible = false;
};

auto GetMenuRender() -> CMenuRender*;