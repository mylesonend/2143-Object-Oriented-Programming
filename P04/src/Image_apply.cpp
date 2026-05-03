// Image::apply — non-destructive convolution
// Returns a new Image; *this is unchanged.
// Add this method to your existing Image.cpp, or paste below your other Image methods.

Image Image::apply(const Kernel& k) const {
    // Start with a full copy of *this so boundary pixels are already filled in
    Image result = *this;

    int half = k.size() / 2;   // for a 3×3 kernel, half = 1

    // Iterate over interior pixels only (skip the outer `half` ring)
    for (int row = half; row < height_ - half; ++row) {
        for (int col = half; col < width_ - half; ++col) {

            double rSum = 0.0, gSum = 0.0, bSum = 0.0;

            // Accumulate the weighted sum over the kernel window
            for (int kr = 0; kr < k.size(); ++kr) {
                for (int kc = 0; kc < k.size(); ++kc) {
                    int srcRow = row + (kr - half);
                    int srcCol = col + (kc - half);

                    const Color& src = pixels_[srcRow][srcCol];
                    double weight    = k.at(kr, kc);

                    rSum += src.r * weight;
                    gSum += src.g * weight;
                    bSum += src.b * weight;
                }
            }

            // Clamp and assign to the output image
            result.pixels_[row][col] = Color(
                static_cast<int>(std::round(rSum)),
                static_cast<int>(std::round(gSum)),
                static_cast<int>(std::round(bSum))
            );
        }
    }

    return result;
}

// ── Extra credit: nearest-neighbor resize ─────────────────────────────────────
Image Image::resize(int newW, int newH) const {
    Image result;
    result.width_  = newW;
    result.height_ = newH;
    result.pixels_.assign(newH, std::vector<Color>(newW));

    for (int r = 0; r < newH; ++r) {
        for (int c = 0; c < newW; ++c) {
            // Map destination pixel back to source with floor (nearest-neighbor)
            int srcRow = static_cast<int>(std::floor(
                static_cast<double>(r) * height_ / newH));
            int srcCol = static_cast<int>(std::floor(
                static_cast<double>(c) * width_  / newW));

            // Clamp to valid range (shouldn't be needed, but safe)
            srcRow = std::min(srcRow, height_ - 1);
            srcCol = std::min(srcCol, width_  - 1);

            result.pixels_[r][c] = pixels_[srcRow][srcCol];
        }
    }

    return result;
}
