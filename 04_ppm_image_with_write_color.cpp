#include <fstream>
#include <iostream>
#include "05_ppm_file_writer.h"




int main()
{
    int image_width = 2560;
    int image_height = 2560;
    write_ppm_file(/* filename= */"ppm_image.ppm", image_width, image_height);
   return 0;
}