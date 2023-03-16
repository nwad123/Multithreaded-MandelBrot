//Engineer: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: Main file

#include "mandelbrot.h"
#include <iostream>
#include <string> // to_string
#include <chrono> // time of program
#include <ctime> // time of program
#include <random>

int main() {
    int a = 5;
    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Size of int (but different)" << sizeof a << std::endl;
}

/*int main() {
    //random number generator initialization
    typedef std::chrono::high_resolution_clock rand_clock;
    //set the beginning of the clock to now
    rand_clock::time_point beginning = rand_clock::now();

    //set a duration counter "d" to the time that has \
    overlapped since the beginning
    rand_clock::duration d = rand_clock::now() - beginning;
    unsigned seed1 = d.count();

    //create a generator engine
    std::default_random_engine rand_gen;
    //seed the generator with the count
    rand_gen.seed(seed1);
    //use a uniform real distibution from 1 to 3
    std::uniform_int_distribution<int> rand_dis(1, 8);
    //set a rand value to the distribution and the generator using std::bind
    int file_style = rand_dis(rand_gen);

    //print a start message to console
    std::cout << "Starting computation with file type: " << file_style
        << std::endl;

    mandelbrot * bmp_ptr;

    //create a new mandelbrot image
    bmp_ptr = new mandelbrot("mandelbrot_10"); // add std::to_string(file_style) if needed
    //switch which file style is based off the random number
    switch(file_style){
        //if file style is one, print basic mandelbrot
        case 1:
            bmp_ptr->fill_out();
            break;
        //if file style is two print the rainbow one
        case 2:
            bmp_ptr->fill_out_rainbow();
            break;
        //if file style is three print the random one
        case 3:
            bmp_ptr->fill_out_random(0, 255, 80);
            break;
        //else print an error
        default: 
            std::cerr << "Random number generation error!\a";
            std::cin.ignore();
    }
    //delete the mandelbrot ptr
    delete bmp_ptr;

    //end clock
    rand_clock::time_point end = rand_clock::now();

    //create the elapsed seconds
    std::chrono::duration<double> computation_time = end-beginning;

    //print out a finished warning
    std::cout << "\aDone! Press Enter to finish";

    //print out how much time it took
    std::cout << "\nGeneration took: " 
        << computation_time.count() << "s\n";
    std::cin.ignore();
    return 0;
}*/