#include "Kernel.h"
#include <stdexcept>
#include <iomanip>

// ── Flat-vector constructor ───────────────────────────────────────────────────
// Unpacks a flat initializer list into data_[row][col].
Kernel::Kernel(int size, std::initializer_list<double> values)
    : size_(size)
{
    if (static_cast<int>(values.size()) != size * size) {
        throw std::invalid_argument("Kernel: values count does not match size*size");
    }

    // Resize the 2-D storage
    data_.assign(size, std::vector<double>(size, 0.0));

    int idx = 0;
    for (double v : values) {
        data_[idx / size][idx % size] = v;
        ++idx;
    }
}

// ── Accessor with bounds check ────────────────────────────────────────────────
double Kernel::at(int row, int col) const {
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        throw std::out_of_range("Kernel::at: index out of range");
    }
    return data_[row][col];
}

// ── Named factories ───────────────────────────────────────────────────────────

Kernel Kernel::identity() {
    //  0  0  0
    //  0  1  0
    //  0  0  0
    return Kernel(3, {
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 0.0
    });
}

Kernel Kernel::boxBlur() {
    //  1/9  1/9  1/9
    //  1/9  1/9  1/9
    //  1/9  1/9  1/9
    const double v = 1.0 / 9.0;
    return Kernel(3, {
        v, v, v,
        v, v, v,
        v, v, v
    });
}

Kernel Kernel::sharpen() {
    //   0  -1   0
    //  -1   5  -1
    //   0  -1   0
    return Kernel(3, {
         0.0, -1.0,  0.0,
        -1.0,  5.0, -1.0,
         0.0, -1.0,  0.0
    });
}

Kernel Kernel::edgeDetect() {
    //  -1  -1  -1
    //  -1   8  -1
    //  -1  -1  -1
    return Kernel(3, {
        -1.0, -1.0, -1.0,
        -1.0,  8.0, -1.0,
        -1.0, -1.0, -1.0
    });
}

Kernel Kernel::emboss() {
    //  -2  -1   0
    //  -1   1   1
    //   0   1   2
    return Kernel(3, {
        -2.0, -1.0,  0.0,
        -1.0,  1.0,  1.0,
         0.0,  1.0,  2.0
    });
}

Kernel Kernel::gaussianBlur() {
    //  1  2  1
    //  2  4  2    ÷ 16
    //  1  2  1
    return Kernel(3, {
        1.0/16, 2.0/16, 1.0/16,
        2.0/16, 4.0/16, 2.0/16,
        1.0/16, 2.0/16, 1.0/16
    });
}

// ── Stream output ─────────────────────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, const Kernel& k) {
    os << std::fixed << std::setprecision(4);
    for (int r = 0; r < k.size(); ++r) {
        os << "[ ";
        for (int c = 0; c < k.size(); ++c) {
            os << std::setw(8) << k.at(r, c);
            if (c + 1 < k.size()) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}
