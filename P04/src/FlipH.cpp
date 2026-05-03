#include "FlipH.h"
#include <algorithm>

void FlipH::apply(Grid& grid) {
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end());
    }
}
