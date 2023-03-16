//Engineer: Nick Waddoups
//Project:  Mandelbrot
//File:     Mandelbrot header

#ifndef MANDELBROT_H
#define MANDELBROT_H

// output size
#define MAND_HEIGHT 25    // height of the image
#define MAND_WIDTH 60     // width of the image

#include <immintrin.h>
#include <iostream>

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

    // Right size of the image x-value
    double x_positive;
    // Left size of the image x-value
    double x_negative;

    // Right size of the image y-value
    double y_positive;
    // Left size of the image y-value
    double y_negative;

public:
    // Basic constructor - no inputs
    //  - Max iterations = 1000
    //  - X range = [-2.2, 0.8]
    //  - Y range is calculated based of image size and 
    mandelbrot() : max_iteration(1000) {
        // allocate 32-byte aligned space for output for AVX compatability
        output = (unsigned int *)( _mm_malloc((sizeof(int) * MAND_WIDTH * MAND_HEIGHT), 32) );
        
        // original x bounds are from [-2.2, 0.8]; We scale the y bounds according
        // to the set height and width
        double y_range = ((double)(MAND_HEIGHT) / (double)(MAND_WIDTH)) * (0.8 - (-2.2));

        // setting the x scaling
        x_positive = 0.8;
        x_negative = -2.2;

        // setting the y scaling
        y_positive = (y_range / 2);
        y_negative = (y_range / 2) * (-1);
    }

    //setter functions
    void set_max_iteration(unsigned int in) { max_iteration = in; }

    // getter functions
    double get_x_range() { return x_positive - x_negative; }
    double get_y_range() { return y_positive - y_negative; }

    // Calculates the mandelbrot set
    void calculate_mandelbrot();

    // Prints it to the terminal (useful for debug)
    void print_to_console();
};

#endif //MANDELBROT_H