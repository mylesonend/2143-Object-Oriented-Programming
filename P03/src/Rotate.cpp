#include "Rotate.h"
#include <stdexcept>

Rotate::Rotate(int degrees) : degrees_(degrees) {
    if (degrees != 0 && degrees != 90 && degrees != 180 && degrees != 270) {
        throw std::invalid_argument("Rotate: angle must be 0, 90, 180, or 270");
    }
}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

// Rotate the image clockwise by degrees_.
//
// 90° CW:  new grid is [width x height] (dimensions swap)
//          result[col][height-1-row] = old[row][col]
//
// 180°:    new grid is [height x width] (dimensions unchanged)
//          result[height-1-row][width-1-col] = old[row][col]
//
// 270° CW: new grid is [width x height] (dimensions swap)
//          result[width-1-col][row] = old[row][col]
void Rotate::apply(Grid& pixels) {
    if (degrees_ == 0) return;

    int height = static_cast<int>(pixels.size());
    int width  = static_cast<int>(pixels[0].size());

    if (degrees_ == 90) {
        // Result dimensions: new_height = width, new_width = height
        Grid result(width, std::vector<Pixel>(height));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[col][height - 1 - row] = pixels[row][col];
            }
        }
        pixels = std::move(result);

    } else if (degrees_ == 180) {
        // Dimensions unchanged
        Grid result(height, std::vector<Pixel>(width));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[height - 1 - row][width - 1 - col] = pixels[row][col];
            }
        }
        pixels = std::move(result);

    } else if (degrees_ == 270) {
        // Result dimensions: new_height = width, new_width = height
        Grid result(width, std::vector<Pixel>(height));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[width - 1 - col][row] = pixels[row][col];
            }
        }
        pixels = std::move(result);
    }
}
