//Engineer: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: mandelbrot cpp

#include "mandelbrot.h"

/*Mandebrot_math
    Summary: does the math of the mandelbrot - REPLACE ALL MATH WITH BEFORE SUBMITTING

    inputs: x (double), y(double)
    outputs: n/a (but it does change the iteration count, which is needed)

*/

unsigned int mandelbrot::mandelbrot_math(double x, double y) {
    //scale x from -2.5 to 1
    x0 = (((x)/(width-1) - 1.25) * 1.75);
    //scale y from -1 to 1
    y0 = (((y)/(height-1) - .5));

    //set iteration, (x,y)1, and intermediate value w to 0
    iteration = x1 = y1 = w = 0;

    //while x1 + y1 are less than or equal to 4, and we haven't reached \
    the max amount of iterations
    while(x1 + y1 <= 4 && iteration < max_iteration) {
        //set x = x1 - y1 + x0
        x = x1 - y1 + x0;
        //set y = w - x1 - y1 + y0
        y = w - x1 - y1 + y0;
        //set x1 to x^2
        x1 = x * x;
        //set y1 to y^2
        y1 = y * y;
        //set w to (x+y)^2
        w = (x + y) * (x + y);
        //count up the iteration
        iteration ++;
    }
    //returns iteration
    return iteration;
}


/*Function: value of pixel, normal mandelbrot
    summary: prints a gratscale mandelbrot image, based off the "fast algorithm"
    from wikipedia

    inputs: x (double), y(double)
    outputs: colorpalette*

    psuedocode:
    begin
        Do the Mandelbrot math

        if the sequence converges return grayscale based on how many
            iterations it took
        else return black
    end
*/
colorpalette * mandelbrot::value_of_pix(double x, double y){

   // do the math of a mandelbrot
   mandelbrot_math(x, y);

   // if the sequence converges print grayscale based on how many \
   iterations it took
   if (iteration < max_iteration) {
        coloredpalette.setrgb(255 - (iteration * iteration)%255, 
            255 - (iteration * iteration)%255, 
            255- (iteration * iteration)%255);
        return &coloredpalette;
    }
    //else return black
    else {
        return &blackpalette;
    }
}

/* Function: fill_out
    summary: fills out the bmp file with a mandelbrot image

    inputs: na
    outputs: na

    psuedocode:
    begin
        open the file
        check if the file is open
            for each row
                for ever column in that row
                    print the value of each pixel to the file
        if the file isn't open print an error
        close the file
    end
*/
void mandelbrot::fill_out() {
    //open the file
    std::fstream output(fname, std::ios::binary | std::ios_base::app);
    if(output.is_open()){
        //for each row
        for(int h = 0; h < 4571; h ++) {
            //for ever column in that row
            for(int v = 0; v < 8000; v ++) {
                //print the value of each pixel to the file
                output << *value_of_pix((double)v, (double)h);
            }
        }
    }
    //if the file isn't open print an error
    else {
        std::cerr << "Couldn't open file!\a";
        std::cin.ignore();
    }
    //close the file
    output.close();
}

/*Function: value_of_pix_rainbow
    summary: returns a rainbow function when the mandelbrot converges

    inputs: x , y (doubles), p_in (colorpalette&)
    outputs: colorpalette *

    psuedocode:
    begin
        do the mandelbrot math
        if the sequence converges return the input palette
        else return black
*/
colorpalette * mandelbrot::value_of_pix_rainbow(double x, double y, colorpalette& p_in) {
    
    //do the mandelbrot math
    mandelbrot_math(x, y);

    //if the sequence converges return the input palette
    if (iteration < max_iteration) {
        return &p_in;
    }
    //else print black
    else {
        return &blackpalette;
    }
}

/*Function: fill_out_rainbow
    summary: fills out a rainbow mandelbrot to a bmp file

    inputs: n/a
    outputs: n/a

    psuedocode:
    begin
        open the file
        initialize rgb values

        if the file is open
            for every row
                reset the RGB values to red
                for every column in each row
                    set the colored pixel palette
                    print the value of each pixel
                    cycle rgb through the rainbow
        else print an error in opening the file

        close the file
    end
*/
void mandelbrot::fill_out_rainbow(){
    //open the file
    std::fstream output(fname, std::ios::binary | std::ios_base::app);
    
    //rgb values
    uchar_16 r, g, b;

    //if the file is open
    if(output.is_open()){
        //go through row
        for(int h = 0; h < 4571; h ++) {
            //reset the rgb values so that each line starts the same
            r = 255;
            g = 0;
            b = 0;
            //for every column in each row
            for(int v = 0; v < 8000; v ++) {

                //set the colored pixel palette
                coloredpalette.setrgb( 
                    (255 - (iteration * iteration)%127) + (r / 2),
                    (255 - (iteration * iteration)%127) + (g / 2),
                    (255 - (iteration * iteration)%127) + (b / 2));
                
                //print the value of each pixel
                output << *value_of_pix_rainbow((double)v, (double)h, coloredpalette);

                //cycle through the rgb rainbow
                if(v % 2 == 0) {
                    if(r == 255 && g != 255 && b ==0) {
                        g ++;
                    }
                    else if(r != 0 && g == 255 && b == 0) {
                        r --;
                    }
                    else if(r == 0 && g == 255 && b != 255) {
                        b ++;
                    }
                    else if(r == 0 && g != 0 && b == 255) {
                        g --;
                    }
                    else if(r != 255 && g == 0 && b == 255) {
                        r ++;
                    }
                    else if(r == 255 && g == 0 && b != 0) {
                        b --;
                    }
                    else {
                        r = 255;
                        g = 0;
                        b = 0;
                    }
                }
                

            }
        }
    }
    //else print an error in opening the file
    else {
        std::cerr << "Couldn't open file!\a";
        std::cin.ignore();
    }
    //close the file
    output.close();
}

/*function: random_palette
    summary: determines the value of a pixel based on whether or not it
        converges, and prints white to it if there is a change in iterations
        on either side of it. If it converges but doesn't change around the
        point then it prints whatever rgb value is entered. 

        If it diverges for 'a' iterations, then print black

    inputs: x, y (double), r, g, b (uchar_16)
    outputs: colorpalette *

    psuedocode:
    begin
        We will test each point around the main point. If any of them are a
        different value than the main point, we will point white
        we do this by doing mandelbrot math for each point

        if the sequence converges print colors
            if one point around the main point is different than the main point
                return white
            else return a the colored palette
                return the colored palette set to the input rgb
        else return black
    end
*/
colorpalette * mandelbrot::random_palette(double x, double y, 
    uchar_16 r, uchar_16 g, uchar_16 b) {
    /* We will test each point around the main point. If any of them are a
    different value than the main point, we will point white
    we do this by doing mandelbrot math for each point
    */
    unsigned int main_pt, left_pt, right_pt, up_pt, down_pt;    
    left_pt = mandelbrot_math((x+1), y);
    right_pt = mandelbrot_math((x-1), y);
    up_pt = mandelbrot_math(x, (y+1));
    down_pt = mandelbrot_math(x, (y-1));
    main_pt = mandelbrot_math(x, y);

    //if the sequence converges print colors
    if (iteration < max_iteration) {
        //if one point around the main point is different than the main point\
        return white
        if(main_pt != left_pt || main_pt != right_pt 
            || main_pt != up_pt || main_pt != down_pt){
            return &whitepalette;
        }
        //else return a the colored palette
        else{
            //return the colored palette set to the input rgb
            coloredpalette.setrgb(
                (127 - (iteration * iteration)%127) + (r / 2)%127,
                (127 - (iteration * iteration)%127) + (g / 2)%127,
                (127 - (iteration * iteration)%127) + (b / 2)%127);
            return &coloredpalette;
        }
    }
    //else return black
    else {
        return &blackpalette;
    }
}

/*Function: fill_out_random
    summary: creates a mandelbrot bmp image with random colors
    based off and rgb multplier
    
    inputs: redmul, greenmul, bluemul (int)
    outputs: n/a

    psuedocode:
    begin
        make a clock (high resolution, from std::chrono)
        set the beginning to now

        set a duration counter "d" to the time that has \
        overlapped since the beginning

        create a generator engine
        seed the generator with the count
        use a uniform real distibution from 0 to 256
        set a rand value to the distribution and the generator using std::bind

        open the file
            if the file is open 
                go through row
                    in each row hit every column
                        print the value of each pixel based on the rand 
                        generator times the multiplier for each value, 
                        basically creating a nonsensical random number
        else print a error that the file couldn't be opened
        close the file
*/
void mandelbrot::fill_out_random(int redmul, int greenmul, int bluemul) {
    //make a clock (high resolution, from std::chrono)
    typedef std::chrono::high_resolution_clock rand_clock;
    //set the beginning to now
    rand_clock::time_point beginning = rand_clock::now();

    //set a duration counter "d" to the time that has \
    overlapped since the beginning
    rand_clock::duration d = rand_clock::now() - beginning;
    unsigned seed1 = d.count();

    //create a generator engine
    std::default_random_engine gen_one;
    //seed the generator with the count
    gen_one.seed(seed1);
    //use a uniform real distibution from 0 to 255
    std::uniform_real_distribution<double> gen_one_dis(0,255);
    //set a rand value to the distribution and the generator using std::bind
    auto rand_val = std::bind (gen_one_dis, gen_one);

    //open the file
    std::fstream output(fname, std::ios::binary | std::ios_base::app);
    //if the file is open 
    if(output.is_open()){
        //go through row
        for(int h = 0; h < 4571; h ++) {
            //in each row hit every column
            for(int v = 0; v < 8000; v ++) {
                //print the value of each pixel based on the rand generator\
                times the multiplier for each value, basically creating a \
                nonsensical random number
                output << *random_palette((double)v, (double)h, 
                rand_val() * redmul, rand_val() * greenmul, 
                rand_val() * bluemul);
            }
        }
    }
    // else print a error that the file couldn't be opened
    else {
        std::cerr << "Couldn't open file!";
        std::cin.ignore();
    }
    //close the file
    output.close();
}