#ifndef COLOR_H
#define COLOR_H

#include "02_vec3.h"
#include <iostream>
#include <fstream>
#include <cmath>
using color = vec3;

using std::ofstream;

void write_color(ofstream &output_stream, const color& pixel_color)
{
    int red =  static_cast<int>(ceil(pixel_color.x() * 255));
    int green = static_cast<int>(ceil(pixel_color.y() * 255));
    int blue = static_cast<int>(ceil(pixel_color.z() * 255));
    output_stream << red << ' ' << green << ' ' << blue << std::endl;
}

#endif