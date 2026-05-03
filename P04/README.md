# P04 — README additions

## Example commands

```bash
# 1. Grayscale then edge-detect — reveals structure in the image
./imgtool output.png out.png --grayscale --edgeDetect

# 2. Gaussian blur followed by sharpen — softens noise, then re-crisp edges
./imgtool output.png out.png --gaussian --sharpen

# 3. Emboss effect on the original color image
./imgtool output.png out.png --emboss

# 4. Flip horizontally, brighten, then sharpen — mix of P03 and P04 filters
./imgtool output.png out.png --flipH --brighten 20 --sharpen

# 5. Full pipeline: flip vertical, grayscale, gaussian blur
./imgtool output.png out.png --flipV --grayscale --gaussian
```

## HSL algorithm

I used the standard HSL → RGB conversion algorithm via chroma (C), hue sector
(H'), and intermediate value (X):

    C  = (1 − |2L − 1|) × S
    H' = H / 60
    X  = C × (1 − |H' mod 2 − 1|)

Then assign (R₁, G₁, B₁) based on which sector [0,6) H' falls in, and add
the lightness-match value m = L − C/2 to each channel before scaling to 255.

**Test case verified manually:**
- Input:  HSL(120, 1.0, 0.5)
- Expected: RGB(0, 255, 0) — pure green
- C = (1 − |2(0.5) − 1|) × 1.0 = 1.0; H' = 2.0; X = 0.0; sector 1 → (R₁,G₁,B₁) = (0, 1, 0); m = 0
- Result: (0, 255, 0) ✓

Edge cases handled:
- s = 0 → returns a pure gray (lightness only), no hue computation.
- h = 360.0 → silently wrapped to 0.0 (same color as h = 0).
- Out-of-range inputs throw `std::invalid_argument`.

## Color operator refactoring

I refactored `Grayscale.cpp` to use `Color` operators. The P03 version wrote
directly to the three fields (`p.r = p.g = p.b = gray`). The P04 version uses
`operator[]` to read the channels and the `Color(int, int, int)` constructor to
write the result:

```cpp
// P04 style
int gray = (p[0] + p[1] + p[2]) / 3;
p = Color(gray, gray, gray);
```

This is cleaner because it treats the pixel as an opaque value rather than a
struct with public fields, and it demonstrates that `operator[]` makes
channel-generic code possible (e.g. you can loop over channels 0–2 without
naming r/g/b explicitly).
