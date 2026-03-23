# Program 2 - Command Line Argument Parser

## Description

This program implements a command-line argument parser for an image processing tool called imgtool

The program reads command-line arguments, validates them, and stores them in a structured Args class. It does not perform image processing — only parsing and validation.

# How to compile 

g++ main.cpp args_deux.cpp -o imgtool

# Valid Examples

./imgtool input.png output.png --grayscale

./imgtool input.png output.png -b 20 -r 90

./imgtool input.png output.png --brighten =50 --blur

# Invalid Examples

./imgtool input.png

./imgtool input.png output.png --brighten 999
