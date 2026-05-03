#include "FlipV.h"
#include <algorithm>

void FlipV::apply(Grid& grid) {
    std::reverse(grid.begin(), grid.end());
}
