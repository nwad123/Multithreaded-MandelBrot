// Engineer: Nick Waddoups - A02276112
// Project: Mandelbrot
// File: Main file

#include "Threadpool.h"
#include "mandelbrot.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {

  std::cout << "x, y, elapsed-time-ms" << std::endl;

  for (size_t a = 256; a < 10000; a *= 2) {
    mandelbrot mb(a, a);

    const auto start = std::chrono::high_resolution_clock::now();

    mb.calculate_mandelbrot_st();

    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << a << ", " << a << ", " << elapsed.count() << std::endl;
  }
  // mandelbrot mb_m;
  // mb_m.calculate_mandelbrot_mt();
  // mb_m.print_to_console();

  // mandelbrot mb_m1(2048, 4096);
  // mb_m1.calculate_mandelbrot_mt();

  // Threadpool tp;
  // for (int a = 0; a < 15; a++) {
  //   tp.add_job(&print);
  // }
  //
  // while (tp.busy()) {
  //   std::cout << "Waiting..." << std::endl;
  //   std::this_thread::sleep_for(500ms);
  // }
  //
  // tp.stop();
}
