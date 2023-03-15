//Engineer: Nick Waddoups
//Project: Mandelbrot
//File: Mandelbrot header

#ifndef MANDELBROT_H
#define MANDELBROT_H

//library
#include "bmp.h"
#include <chrono>
#include <random>
#include <functional>

//class definition \
mandelbrot is derived from bitmap_file
class mandelbrot : public bitmap_file {
private:
    //max iteration var, default is 1000. same for all mandelbrots
    unsigned int max_iteration;
    //iteration counter
    unsigned int iteration;
    //doubles for pixel values, used in value_of_pix functions
    double x0, y0, x1, y1, w;
    //number for changing the scale. Bigger = smaller picture
    double a;
    //number for changing the x position
    double b;
    //number for changing the y position
    double c;
    //color palette, the colored palette gets changed in \
    value_of_pix functions which the black palette is a \
    simple black one
    colorpalette coloredpalette, blackpalette, whitepalette;
public:
    //constructor that opens
    mandelbrot(std::string filename) : bitmap_file(filename),
    max_iteration(1000), iteration(0), a(1), b(0), c(0) {
        whitepalette.setrgb(255, 255, 255);
    }

    //pointer to the color palette for each pixel (basic)
    colorpalette * value_of_pix(double x, double y);

    /*pointer to the color palette for each pixel with 
      options for preset palettes
        0: grayscale
        1: reds/oranges
        2: greens/blues
        3: purples/blacks
        4: rainbow (not working rn)*/
    colorpalette * value_of_pix_color_presets(double x, double y, 
        uchar_16 preset_num);

    /*pointer to the color paletter for each pixel, with 
      different tranformations
        0: image is reversed horizontally
        1: image is rotated 90 degrees to the right
        2: image is rotated 90 degrees to the left
        3: image is mirrored over center access*/
    colorpalette * value_of_pix_transformations(double x, double y, 
        uchar_16 transform);

    //prints crazy rainbow shiz
    colorpalette * value_of_pix_rainbow(double x, double y, 
        colorpalette& p_in);

    //prints random stuff
    colorpalette * random_palette(double x, double y, uchar_16 r, 
        uchar_16 g, uchar_16 b);
    colorpalette * value_of_pix_r(double x, double y);

    //fills out a black and white mandelbrot image (basic)
    void fill_out();
    void fill_out_rainbow();
    void fill_out_random(int redmul, int greenmul, int bluemul);

    //setter functions
    void set_a(double in) { a = in; }
    void set_b(double in) { b = in; }
    void set_c(double in) { c = in; }
    void set_maxiteration(unsigned int in) { max_iteration = in; }

    //mandelbrot function (makes it easier to read/program)
    unsigned int mandelbrot_math(double x, double y);
};

#endif //MANDELBROT_H