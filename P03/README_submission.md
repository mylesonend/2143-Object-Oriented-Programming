# P03 Submission Notes

## Grayscale Formula Choice

I used the **luminance (perceptual) formula**:

```
gray = 0.299*r + 0.587*g + 0.114*b
```

**Why:** Human vision is not equally sensitive to all colors. We perceive green most
strongly, red moderately, and blue least. The simple average `(r+g+b)/3` treats all
channels equally and produces a noticeably flat, washed-out result on natural photos.
The luminance weights match the standard ITU-R BT.601 coefficients, which were derived
from measurements of human color perception. The result looks closer to how our eyes
would see the same scene in black-and-white.

---

## Example Commands

### 1. Grayscale only
```bash
./imgtool images/Hulda.jpg out.png --grayscale
```
Converts the image to black and white using the luminance formula.

### 2. Brighten first, then grayscale
```bash
./imgtool images/Hulda.jpg out.png --brighten 60 --grayscale
```
Brightens colors *before* flattening to gray. The extra color brightness is baked in,
so highlights appear lighter in the final grayscale.

### 3. Grayscale first, then brighten (different result from #2)
```bash
./imgtool images/Hulda.jpg out.png --grayscale --brighten 60
```
Converts to gray *first*, then uniformly brightens the gray values.
Because the luminance step already happened, `brighten` just lifts all gray pixels
equally — no color information influences the brightness anymore.

### 4. Full pipeline — grayscale, brighten, blur, flip horizontal
```bash
./imgtool images/Hulda.jpg out.png --grayscale --brighten 30 --blur --flipH
```
Demonstrates four filters chained in sequence. Order matters: grayscale runs first,
so blur and flipH operate on a gray image.

### 5. Rotate 90° then flip vertically
```bash
./imgtool images/Hulda.jpg out.png --rotate 90 --flipV
```
Rotates the image clockwise 90° (swapping width and height), then mirrors
it top-to-bottom. Produces a result that differs from `--flipV --rotate 90`
because the grid dimensions are different at each step.
