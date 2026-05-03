#include "Color.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>

// ── Arithmetic operators ──────────────────────────────────────────────────────

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(double scale) const {
    return Color(
        static_cast<int>(std::round(r * scale)),
        static_cast<int>(std::round(g * scale)),
        static_cast<int>(std::round(b * scale))
    );
}

// Non-member: 0.5 * c  — delegates to c * 0.5
Color operator*(double scalar, const Color& c) { return c * scalar; }

// ── Comparison operators ──────────────────────────────────────────────────────

bool Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b;
}

// operator!= is already defined in Color.h (delegates to ==)

// ── Stream operators ──────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "rgb(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Color& c) {
    int rv, gv, bv;
    is >> rv >> gv >> bv;
    c = Color(rv, gv, bv);   // constructor clamps
    return is;
}

// ── Static factories ──────────────────────────────────────────────────────────

Color Color::fromRGB(int r, int g, int b) {
    return Color(r, g, b);
}

Color Color::fromHex(const std::string& hex) {
    std::string h = hex;

    // Strip optional leading '#'
    if (!h.empty() && h[0] == '#') {
        h = h.substr(1);
    }

    if (h.size() != 6) {
        throw std::invalid_argument("fromHex: expected 6 hex digits, got: " + hex);
    }

    // Validate all characters are hex digits
    for (char ch : h) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            throw std::invalid_argument("fromHex: invalid hex character in: " + hex);
        }
    }

    int rv = std::stoi(h.substr(0, 2), nullptr, 16);
    int gv = std::stoi(h.substr(2, 2), nullptr, 16);
    int bv = std::stoi(h.substr(4, 2), nullptr, 16);

    return Color(rv, gv, bv);
}

Color Color::fromHSL(double h, double s, double l) {
    // Validate inputs
    if (h < 0.0 || h >= 360.0) {
        // Allow exactly 360 as an edge case by wrapping
        if (std::abs(h - 360.0) < 1e-9) {
            h = 0.0;
        } else {
            throw std::invalid_argument("fromHSL: hue must be in [0, 360)");
        }
    }
    if (s < 0.0 || s > 1.0) {
        throw std::invalid_argument("fromHSL: saturation must be in [0, 1]");
    }
    if (l < 0.0 || l > 1.0) {
        throw std::invalid_argument("fromHSL: lightness must be in [0, 1]");
    }

    // Achromatic case (gray) — handles s == 0
    if (s == 0.0) {
        int gray = static_cast<int>(std::round(l * 255.0));
        return Color(gray, gray, gray);
    }

    // HSL → RGB via the standard algorithm
    // Reference: https://www.rapidtables.com/convert/color/hsl-to-rgb.html
    double c  = (1.0 - std::abs(2.0 * l - 1.0)) * s;   // chroma
    double hp = h / 60.0;                                // hue sector [0,6)
    double x  = c * (1.0 - std::abs(std::fmod(hp, 2.0) - 1.0));

    double r1, g1, b1;
    if      (hp < 1.0) { r1 = c; g1 = x; b1 = 0; }
    else if (hp < 2.0) { r1 = x; g1 = c; b1 = 0; }
    else if (hp < 3.0) { r1 = 0; g1 = c; b1 = x; }
    else if (hp < 4.0) { r1 = 0; g1 = x; b1 = c; }
    else if (hp < 5.0) { r1 = x; g1 = 0; b1 = c; }
    else               { r1 = c; g1 = 0; b1 = x; }

    double m = l - c / 2.0;

    int rv = static_cast<int>(std::round((r1 + m) * 255.0));
    int gv = static_cast<int>(std::round((g1 + m) * 255.0));
    int bv = static_cast<int>(std::round((b1 + m) * 255.0));

    return Color(rv, gv, bv);
}

