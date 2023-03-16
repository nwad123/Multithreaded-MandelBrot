//Engineer: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: Main file

#include "mandelbrot.h"
#include <iostream>

int main() {
    mandelbrot mb;
    mb.calculate_mandelbrot();
    mb.print_to_console();
}
