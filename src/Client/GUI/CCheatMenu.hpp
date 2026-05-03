#pragma once

class CCheatMenu final {
public:
    auto OnRenderMenu() -> void;
};

auto GetCheatMenu() -> CCheatMenu*;