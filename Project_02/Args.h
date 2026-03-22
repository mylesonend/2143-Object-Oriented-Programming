#ifndef ARGS_H
#define ARGS_H

#include <string>

class Args {
public:
    // Required
    std::string input;
    std::string output;

    // Flags
    bool grayscale = false;
    bool blur = false;
    bool flipH = false;
    bool flipV = false;

    // Options with values
    bool use_brighten = false;
    int brighten = 0;

    bool use_rotate = false;
    int rotate = 0;

    // Constructor
    Args(int argc, char* argv[]);

    // Print results
    void print() const;
};

#endif