#pragma once

class CConfig final {
public:
    auto Initialize( ) -> bool;
    auto Save( ) -> bool;
};

auto GetConfig() -> CConfig*;
