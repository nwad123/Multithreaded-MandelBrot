// Engineer: Nick Waddoups
// Project:  Mandelbrot
// File:     Mandelbrot cpp

#include "mandelbrot.h"

void mandelbrot::calculate_mandelbrot_range(const size_t row_begin,
                                            const size_t row_end) {
  // mandelbrot variables
  double x, y, x_loop(0), x_temp(0), y_loop(0);

  // scaling variables
  double x_step = get_x_range() / (double)(width);
  double y_step = get_y_range() / (double)(height);

  // Loop variables
  size_t row(0), col(0), iteration(0);

  // Set x to it's leftmost position
  x = x_negative;
  y = y_positive - ((double)row_begin * y_step);

  // Row loops
  for (row = row_begin; row <= row_end; row++) {
    // Column loops
    for (col = 0; col < width; col++) {
      // Reset internal calculation variables
      x_loop = 0;
      x_temp = 0;
      y_loop = 0;

      // Iterations for each point
      for (iteration = 0; ((x_loop * x_loop) + (y_loop * y_loop) < 4) &&
                          (iteration < max_iteration);
           iteration++) {

        // update x and y loop variables
        x_temp = (x_loop * x_loop) - (y_loop * y_loop) + x;
        y_loop = (2.0 * x_loop * y_loop) + y;
        x_loop = x_temp;

      } // iterations

      // Set matrix point to be the iteration count
      output[(row * width) + col] = iteration;

      // Update x position
      x = x + x_step;
    } // columns

    // Update x and y positions
    x = x_negative;
    y = y - y_step;

  } // rows
} // fn calculate_mandelbrot_range()

void mandelbrot::calculate_mandelbrot_st() {
  calculate_mandelbrot_range(0, height - 1);
} // fn calculate_mandelbrot()

void mandelbrot::calculate_mandelbrot_mt() {
  // divide up the rows
  unsigned int number_of_rows_per_thread = (height / number_of_threads) + 1;

  // initially set the starting row to 0 (as that is the first row)
  size_t starting_row = 0;
  // set the ending row for this first set to the number of rows it should use
  size_t ending_row = starting_row + number_of_rows_per_thread;

  // assign work to each thread
  while (ending_row < height) {
    // print thread information to std error
    std::cout << "Assigning thread to rows " << starting_row << " and "
              << ending_row << std::endl;

    // assign work to the threads
    threads.push_back(std::thread(&mandelbrot::calculate_mandelbrot_range, this,
                                  starting_row, ending_row));

    // updating the row positions for the next thread
    starting_row = ending_row + 1;
    ending_row = starting_row + number_of_rows_per_thread;
  }

  // assign the final rows to the last thread
  ending_row = height - 1;

  std::cout << "Assigning final thread to rows " << starting_row << " and "
            << ending_row << std::endl;

  threads.push_back(std::thread(&mandelbrot::calculate_mandelbrot_range, this,
                                starting_row, ending_row));

  // allow threads to finish
  for (auto &t : threads) {
    if (t.joinable()) {
      std::cout << "Joining thread " << t.get_id() << std::endl;
      t.join();
    }
  }
}

void mandelbrot::print_to_console() {
  // Loop variables
  size_t row, col;

  // Character to print
  char print;

  // Iteration at point
  unsigned int iteration;

  // Row loops
  for (row = 0; row < height; row++) {
    // Column loops
    for (col = 0; col < width; col++) {
      // get the iteration
      iteration = output[(row * width) + col];

      // Calculate the value of the character
      print = (iteration == max_iteration) ? '@'
              : (iteration > 10)           ? '+'
              : (iteration > 5)            ? '-'
                                           : ' ';

      // Print the character to the console
      std::cout << print;
    }
    // add a new line
    std::cout << std::endl;
  }
}
