//Name: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: Bitmap header

#ifndef BMP_H
#define BMP_H

//libraries used
#include <iostream> // error messages
#include <fstream>  // file creation of the bmp
#include <array>    // header file declarations
#include <string>   // file name

typedef unsigned char uchar_16;

//24 bit color pallette
class colorpalette {
private:
    //saves the one byte unsigned characters for red, green, and blue
    uchar_16 b;
    uchar_16 g;
    uchar_16 r;
public:
    //constructor: sets rgb to 000, which is black
    colorpalette() : b(0x00), g(0x00), r(0x00) {}
    //overloads the << operator for ease of outputting a pixel \
    to a file
    
    friend std::ostream & operator << (std::ostream &out, 
        colorpalette &pal);

    //sets r,g,b values
    void setrgb(uchar_16 red, uchar_16 green, uchar_16 blue);

    /*sets rgb values to some different presets
    input_value:
        sets the intensity of the colors
    variations:
        0: grayscale
        1: reds/oranges
        2: greens/blues
        3: purples/blacks*/
    void presetpalettes(uchar_16 input_value, uchar_16 variation);
};

//bitmap file definition
class bitmap_file {
private:
    //BMP Header
    std::array<unsigned char, 14> bmp_header = {
    0x42, 0x4d, // "BM" file header to declare file type
    0x76, 0xf3, 0x89, 0x06, // size of the BMP file
    0x00, 0x00, 
    0x00, 0x00, // unused, they are application specific
    0x36, 0x00, 0x00, 0x00  // offset where the pixel array can be found
    };
    //DIB Header
    std::array<unsigned char, 40> dib_header = {
    0x28, 0x00, 0x00, 0x00, // number of bytes in the DIB header
    0x40, 0x1f, 0x00, 0x00, // width of the pixel array (8000)
    0xdb, 0x11, 0x00, 0x00, // height of the pixel array (bottom to top) (4571)
    0x01, 0x00, // 1 color plane
    0x18, 0x00, // 24 bit color per pixel
    0x00, 0x00, 0x00, 0x00, // 0 is no compression
    0x40, 0xf3, 0x89, 0x06, // size of the raw bitmap data
    0x13, 0x0b, 0x00, 0x00, // print width horizontal
    0x13, 0x0b, 0x00, 0x00, // print width vertical
    0x00, 0x00, 0x00, 0x00, // color palette
    0x00, 0x00, 0x00, 0x00  // important colors
    };
protected:
    //filename
    std::string fname;
    //width and height
    unsigned int width = 8000;
    unsigned int height = 4571;
public:
    //contructor creates a .bmp file with this name
    bitmap_file(std::string);
};

#endif //BMP_H