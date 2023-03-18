// Engineer: Nick Waddoups
// Project:  Mandelbrot
// File:     Mandelbrot header

#ifndef MANDELBROT_H
#define MANDELBROT_H

// default output size
#define MAND_HEIGHT 35 // height of the image
#define MAND_WIDTH 50  // width of the image

#include <immintrin.h>
#include <iostream>
#include <thread>
#include <vector>

// Mandelbrot Class
//  - stores mandelbrot iterations in an array
//  - X: [-2.2, 0.8]
//  - Y: [-1.2, 1.2]
class mandelbrot {
private:
  // Mandelbrot Matrix [height][width]
  //  - Stores the iteration count for the mandelbrot image
  unsigned int *output;

  // Maximum mandelbrot iteration
  //  - Higher values lead to more accurate results, lower values
  //    calculate faster
  unsigned int max_iteration;

  // image height and width
  size_t height;
  size_t width;

  // Right size of the image x-value
  double x_positive;
  // Left size of the image x-value
  double x_negative;

  // Right size of the image y-value
  double y_positive;
  // Left size of the image y-value
  double y_negative;

  // Threads
  unsigned int number_of_threads;
  std::vector<std::thread> threads;

  // Calculates the mandelbrot set for a given range
  void calculate_mandelbrot_range(const size_t, const size_t);

public:
  // Basic constructor - no inputs
  //  - Max iterations = 1000
  //  - X range = [-2.2, 0.8]
  //  - Y range is calculated based of image size and
  mandelbrot()
      : max_iteration(1000), height(MAND_HEIGHT), width(MAND_WIDTH),
        x_positive(0.8), x_negative(-2.2) {

    // allocate 32-byte aligned space for output for AVX compatability
    output = (unsigned int *)(_mm_malloc((sizeof(int) * height * width), 32));
    // default x bounds are from [-2.2, 0.8]; We scale the y bounds according
    // to the set height and width
    double y_range = ((double)(height) / (double)(width)) * (0.8 - (-2.2));

    // setting the y scaling
    y_positive = (y_range / 2);
    y_negative = (y_range / 2) * (-1);

    // set up the number of threads to be the maximum number of rows
    number_of_threads = std::thread::hardware_concurrency();
    threads.resize(number_of_threads);
  }

  // Constructor 1 - image size inputs
  //  - Max iterations = 1000
  //  - X range = [-2.2, 0.8]
  //  - inputs h and w correspond to height and width, respectively
  mandelbrot(size_t h, size_t w)
      : max_iteration(1000), x_positive(0.8), x_negative(-2.2) {

    // set height and width input values
    height = h;
    width = w;

    // allocate 32-byte aligned space for output for AVX compatability
    output = (unsigned int *)(_mm_malloc((sizeof(int) * height * width), 32));
    // default x bounds are from [-2.2, 0.8]; We scale the y bounds according
    // to the set height and width
    double y_range = ((double)(height) / (double)(width)) * (0.8 - (-2.2));

    // setting the y scaling
    y_positive = (y_range / 2);
    y_negative = (y_range / 2) * (-1);

    // set up the number of threads to be the maximum number of rows
    number_of_threads = std::thread::hardware_concurrency();
    threads.resize(number_of_threads);
  }
  // Basic destructor
  ~mandelbrot() {}

  // setter functions
  void set_max_iteration(unsigned int in) { max_iteration = in; }

  // getter functions
  double get_x_range() { return x_positive - x_negative; }
  double get_y_range() { return y_positive - y_negative; }

  // Calculates the mandelbrot set using a single thread
  void calculate_mandelbrot_st();

  // Calculate the mandelbrot set using multiple threads
  void calculate_mandelbrot_mt();

  // Prints it to the terminal (useful for debug)
  void print_to_console();
};

#endif // MANDELBROT_H
