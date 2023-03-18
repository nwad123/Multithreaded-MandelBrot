// Engineer: Nick Waddoups - A02276112
// Project: Mandelbrot
// File: Main file

#include "mandelbrot.h"
#include <iostream>
#include <thread>

int main() {
  // mandelbrot mb;
  // mb.calculate_mandelbrot_st();
  // mb.print_to_console();

  // mandelbrot mb_m;
  // mb_m.calculate_mandelbrot_mt();
  // mb_m.print_to_console();

  mandelbrot mb_m1(2048, 4096);
  mb_m1.calculate_mandelbrot_mt();
}
