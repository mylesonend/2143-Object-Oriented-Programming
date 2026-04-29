#include "Grayscale.h"

// Luminance formula: perceptually weighted average
// Human eyes are most sensitive to green, less to red, least to blue.
// This produces a more natural-looking grayscale than a simple (r+g+b)/3 average.
void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (auto& p : row) {
            int gray = static_cast<int>(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);
            p.r = p.g = p.b = gray;
        }
    }
}
