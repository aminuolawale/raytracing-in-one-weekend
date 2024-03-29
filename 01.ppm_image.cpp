#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    int image_width = 2560;
    int image_height = 2560;
    ofstream ppmFile;
    ppmFile.open("ppm_image.ppm");

    // Specify format and dimension of image
    ppmFile
        << "P3\n"
        << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j)
    {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_width - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    clog << "\rDone.  \n";
    return 0;
}