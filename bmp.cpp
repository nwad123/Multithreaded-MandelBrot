//Name: Nick Waddoups - A02276112
//Project: Mandelbrot
//File: Bitmap code

#include "bmp.h"

//outputs 3 bytes of data, red, green, and blue, but in \
gbr output format
std::ostream & operator << (std::ostream &out, colorpalette &pal) {
    out << pal.b << pal.g << pal.r;
    return out;
}

//simpy sets r, g, and b
void colorpalette::setrgb(uchar_16 red, uchar_16 green, uchar_16 blue){
    r = red;
    g = green;
    b = blue;
}

//sets the palette to a certain variation
void colorpalette::presetpalettes(uchar_16 input_value, uchar_16 variation){
    switch(variation) {
        //grayscale sexiness
        case 0: setrgb((input_value * input_value)%255,   // r
                (input_value * input_value)%255,          // g
                (input_value * input_value)%255);         // b
            break;
        //red/oranges
        case 1: setrgb((input_value * input_value)%255,   // r
                (input_value * input_value)%80,           // g
                0);                                       // b
            break;
        //blues/greens
        case 2: setrgb(0,                                 // r
                (input_value * input_value)%255,          // g
                (input_value * input_value)%200);         // b
            break;
        //purples/blacks
        case 3: setrgb((input_value * input_value)%160,   // r
                (input_value * input_value)%20,           // g
                (input_value * input_value)%90);          // b
            break;
        //rainbow
        case 4: setrgb((input_value * input_value)%255,   // r
                (input_value * input_value)%255,          // g
                (input_value * input_value)%255);         // b
            break;
        default:
            break;
    }
}

bitmap_file::bitmap_file(std::string filename) {
    //save the filename
    fname = filename + ".bmp";

    //open the file for writing in binary, appending .bmp to it
    std::ofstream output(fname, std::ios::binary);
    
    //if the file opened successfully
    if(output.is_open()){
        //print the bit map header
        for(int i = 0; i < 14; i ++) {
            output << bmp_header.at(i);
        }
        //print the dib header
        for(int i = 0; i < 40; i ++) {
            output << dib_header.at(i);
        }
    }
    //else print an error
    else {
        std::cerr << "Couldn't open file!";
        std::cin.ignore();
    }
    //close the file at this time
    output.close();
}