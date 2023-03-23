// Engineer: Nick Waddoups - A02276112
// Project: Mandelbrot
// File: Main file

#include "Threadpool.h"
#include "mandelbrot.h"
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

int main() {
  mandelbrot mb_m;
  mb_m.calculate_mandelbrot_mt();
  mb_m.print_to_console();

  mandelbrot mb_tp;
  mb_tp.calculate_mandelbrot_tp();
  mb_tp.print_to_console();

  // mandelbrot mb_m1(2048, 4096);
  // mb_m1.calculate_mandelbrot_mt();
}
