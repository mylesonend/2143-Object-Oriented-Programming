#include "Grayscale.h"

// Grayscale filter — refactored for P04 to use Color operators.
//
// P03 style was:
//   int gray = (p.r + p.g + p.b) / 3;
//   p.r = p.g = p.b = gray;
//
// P04 style uses operator[] and the Color constructor instead of
// directly assigning to the three fields — cleaner and demonstrates
// why indexed channel access (operator[]) exists.

void Grayscale::apply(Grid& grid) {
    for (auto& row : grid) {
        for (auto& p : row) {
            int gray = (p[0] + p[1] + p[2]) / 3;
            p = Color(gray, gray, gray);
        }
    }
}

std::string Grayscale::name() const {
    return "grayscale";
}
