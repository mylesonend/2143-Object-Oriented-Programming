#pragma once
#include "Filter.h"
#include <string>

class FlipH : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override { return "flipH"; }
};
