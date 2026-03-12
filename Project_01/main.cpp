#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <cstdlib>

#include "termcolor.hpp"
#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;
using namespace termcolor;

// ------------------------------------------------------------
// ImageTools Class
// ------------------------------------------------------------

class ImageTools {
    string imageName;
    int width;
    int height;
    int channels;
    unsigned char* data;

public:
    ImageTools() {}

    ImageTools(string imgName) : imageName(imgName) {

        data = stbi_load(imageName.c_str(),
                         &width,
                         &height,
                         &channels,
                         3);

        if (!data) {
            cerr << red << "Failed to load image: "
                 << reset << imageName << "\n";
        }

        channels = 3;
    }

    void grayScale() {

        for (int i = 0; i < width * height; ++i) {

            int idx = i * channels;

            int r = data[idx + 0];
            int g = data[idx + 1];
            int b = data[idx + 2];

            int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

            unsigned char gr = static_cast<unsigned char>(gray);

            data[idx + 0] = gr;
            data[idx + 1] = gr;
            data[idx + 2] = gr;
        }
    }

    bool save(string outputPath) {

        if (!stbi_write_png(outputPath.c_str(),
                            width,
                            height,
                            channels,
                            data,
                            width * channels)) {

            cerr << red << "Failed to write output image\n";
            return false;
        }

        return true;
    }

    ~ImageTools() {
        if (data)
            stbi_image_free(data);
    }
};

// ------------------------------------------------------------
// Open image with OS default viewer
// ------------------------------------------------------------

bool open_file_default_app(const std::string& path) {

#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\"";
#endif

    return std::system(cmd.c_str()) == 0;
}

// ------------------------------------------------------------
// Main Program
// ------------------------------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "Usage: ./imgtool <input_image> <output_image>\n";
        return 1;
    }

    string inputPath  = argv[1];
    string outputPath = argv[2];

    ImageTools img(inputPath);

    cout << green << "Loaded image successfully\n" << reset;

    img.grayScale();

    if (!img.save(outputPath)) {
        return 1;
    }

    cout << green << "Saved output to: "
         << yellow << outputPath << reset << "\n";

    cout << "Opening output in default viewer...\n";

    if (!open_file_default_app(outputPath)) {
        cout << yellow
             << "Warning: could not launch viewer automatically.\n"
             << reset;
    }

    return 0;
}