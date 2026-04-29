#include "FlipH.h"
#include <algorithm>

// Mirror each row left-to-right.
// Only iterate to width/2 to avoid swapping each pair twice (which would undo the flip).
void FlipH::apply(Grid& pixels) {
    for (auto& row : pixels) {
        int width = static_cast<int>(row.size());
        for (int col = 0; col < width / 2; ++col) {
            std::swap(row[col], row[width - 1 - col]);
        }
    }
}
