//Engineer: Nick Waddoups
//Project:  Mandelbrot
//File:     Mandelbrot cpp

#include "mandelbrot.h"

void mandelbrot::calculate_mandelbrot() {
    // mandelbrot variables
    double
        x(x_positive),
        y(y_positive),
        x_loop(0),
        x_temp(0),
        y_loop(0);

    // scaling variables
    double x_step = get_x_range() / (double)(MAND_WIDTH);
    double y_step = get_y_range() / (double)(MAND_HEIGHT);

    // Loop variables
    size_t row(0), col(0), iteration(0);

    // Row loops
    for (row = 0; row < MAND_HEIGHT; row++) {
        // Column loops
        for (col = 0; col < MAND_WIDTH; col++) {
            // Reset internal calculation variables
            x_loop = 0;
            x_temp = 0;
            y_loop = 0;

            // Iterations for each point
            for (iteration = 0;
                ((x_loop * x_loop) + (y_loop * y_loop) < 4)
                    && (iteration < max_iteration);
                iteration++) {

                // update x and y loop variables
                x_temp = (x_loop * x_loop) - (y_loop * y_loop) + x;
                y_loop = (2.0 * x_loop * y_loop) + y;
                x_loop = x_temp;

            } // iterations

            // Set matrix point to be the iteration count
            output[(row * MAND_WIDTH) + col] = iteration;

            // Update x position
            x = x + x_step;
        } // columns

        // Update y position
        y = y + y_step;

    } // rows
} // fn calculate_mandelbrot()

void mandelbrot::print_to_console() {
    // Loop variables
    size_t row, col;

    // Character to print
    char print;

    // Iteration at point
    int iteration;

    // Row loops
    for (row = 0; row < MAND_HEIGHT; row++) {
        // Column loops
        for (col = 0; col < MAND_WIDTH; col++) {
            // get the iteration
            iteration = output[(row * MAND_WIDTH) + col];

            // Calculate the value of the character
            print =
                (iteration == max_iteration) ? '@' :
                (iteration > 750) ? '+' :
                (iteration > 500) ? '-' : 
                ' ';

            // Print the character to the console
            std::cout << print;
        }
        // add a new line
        std::cout << std::endl;
    }
}