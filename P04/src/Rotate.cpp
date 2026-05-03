#include "Rotate.h"

// Rotates the image 90° clockwise.
// A pixel at (row, col) in the original goes to (col, height-1-row) in the result,
// which means a grid of size [H][W] becomes [W][H].

void Rotate::apply(Grid& grid) {
    if (grid.empty()) return;

    int H = static_cast<int>(grid.size());
    int W = static_cast<int>(grid[0].size());

    // Build a transposed grid: new size is [W][H]
    Grid rotated(W, std::vector<Color>(H));

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            rotated[c][H - 1 - r] = grid[r][c];
        }
    }

    grid = std::move(rotated);
}
