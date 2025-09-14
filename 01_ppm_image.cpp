#include <iostream>
#include <fstream>


using namespace std;

ofstream getFile();

int main() {
    // Specify image dimensions.
    int image_with = 256;
    int image_height = 256;

    // Create and open a .ppm file.
    ofstream ppmFile = getFile();

    // Specify the format and dimension of the image.
    ppmFile << "P3" <<endl << image_with << ' ' << image_height << endl << "255" << endl;

    // Write the pixel data to the file.
    for (int j = 0; j < image_height; j++) {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_with; i++) {
            int red = ((i+1.0)/image_with) * 255;
            int green = ((j+1.0)/image_height) * 255;
            int blue = 0;
            ppmFile << red << ' ' << green << ' ' << blue << endl;
        }
    }
    clog << "Done." << endl;
    ppmFile.close();

    return 0;
}


// Function to create and return an opened file stream.
ofstream getFile() {
    ofstream ppmFile;
    ppmFile.open("ppm_image.ppm");
    return ppmFile;
}