#pragma once

class CCheatMenu final {
public:
    auto OnRenderMenu() -> void;
    auto OnEspPreviewRender() -> void;
};

auto GetCheatMenu() -> CCheatMenu*;