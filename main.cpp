// Engineer: Nick Waddoups - A02276112
// Project: Mandelbrot
// File: Main file

#include "mandelbrot.h"
#include <iostream>
#include <thread>

int main() {
  mandelbrot mb;
  mb.calculate_mandelbrot_st();
  mb.print_to_console();
}
