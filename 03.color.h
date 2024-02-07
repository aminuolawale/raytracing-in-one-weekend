#ifndef COLOR_H
#define COLOR_H

#include "02.vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream &out, color pixel_color)
{
    out << static_cast<int>(ceil(255 * pixel_color.x())) << ' '
        << static_cast<int>(ceil(255 * pixel_color.y())) << ' '
        << static_cast<int>(ceil(255 * pixel_color.z())) << '\n';
}

#endif