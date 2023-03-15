//Engineer: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: mandelbrot bitmap

#ifndef MAND_BMP_H
#define MAND_BMP_H

//libraries
#include "mandelbrot.h"

//class definition
class bmp_mand : public mandelbrot {
private:
    std::string fname;
    uchar_16 palette = 0;
    uchar_16 transformation = 0xff;
    double a = 1;
public:
    bmp_mand(std::string filename) : mandelbrot(filename) {}
};

#endif //MAND_BMP_H