#ifndef PPM_FILE_WRITER_H
#define PPM_FILE_WRITER_H


#include "03_color.h"
#include <iostream>
#include <fstream>

void write_ppm_header(std::ofstream &ppmFile, int image_width, int image_height)
{
    ppmFile << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";
}


color get_pixel_color(int row_index, int col_index, int image_width, int image_height)
{
    double red_value = (col_index + 1.0) / image_width;
    double green_value = (row_index + 1.0) / image_height;
    double blue_value = 0.0;
    return color(red_value, green_value, blue_value);
}

void write_ppm_file(const std::string &filename, int image_width, int image_height)
{
    std::ofstream ppmFile;
    ppmFile.open(filename);
    write_ppm_header(ppmFile, image_width, image_height);
    for (int i = 0; i < image_height; ++i)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j)
        {
            color pixel_color = get_pixel_color(/* row_index= */ i, /* col_index= */ j, image_width, image_height);
            write_color(ppmFile, pixel_color);
        }
    }
    std::clog << "\rDone. " << std::endl;
    ppmFile.close();
}




#endif
