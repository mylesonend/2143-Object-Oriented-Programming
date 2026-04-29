#include "FlipV.h"
#include <algorithm>

// Mirror the image top-to-bottom by swapping entire rows.
// std::swap on vector<Pixel> swaps the full row in one efficient call.
// Only iterate to height/2 to avoid double-swapping rows back to original.
void FlipV::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    for (int row = 0; row < height / 2; ++row) {
        std::swap(pixels[row], pixels[height - 1 - row]);
    }
}
