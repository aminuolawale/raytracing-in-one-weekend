#include "03.color.h"
#include "02.vec3.h"
#include <fstream>
#include <iostream>

int main() {
    int image_width = 2560;
    int image_height = 2560;

    std::ofstream ppmFile;
    ppmFile.open("ppm_image2.ppm");
    ppmFile << "P3\n" << image_width << ' ' <<image_height << "\n255\n";
    for (int i=0; i < image_height; ++i) {
        std::clog << "\rScanlines remaining: " << (image_height -i) << ' ' << std::flush;
        for (int j=0; j < image_width; ++j){
            write_color(ppmFile,  color((j+1.0)/image_width, (i+1.0)/image_height, 0.0));
        }
    }
    std::clog << "\rDone. "<< std::endl;
    return 0;
}