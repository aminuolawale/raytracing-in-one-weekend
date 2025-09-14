#include <iostream>
#include <fstream>
#include "02_vec3.h"
#include "03_color.h"
#include "06_ray.h" 
#include "05_ppm_file_writer.h"

using namespace std;

int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = static_cast<int>(ceil(image_width / aspect_ratio));
    image_height = image_height > 0 ? image_height : 1;
    double actual_aspect_ratio = static_cast<double>(image_width) / image_height;

    double viewport_height = 2.0;
    double viewport_width = viewport_height * actual_aspect_ratio;

    // Distance between the camera and the viewport plane in 3D space.
    double focal_length = 1.0;
    point3 camera_center = point3();

    // Pixel grid vectors
    vec3 viewport_u = vec3(viewport_width, 0, 0);   // Row vector from the top left corner rightwards.
    vec3 viewport_v = vec3(0, -viewport_height, 0); // Column vector from the top left corner downwards.
    vec3 pixel_delta_u = unit_vector(viewport_u);
    vec3 pixel_delta_v = unit_vector(viewport_v);

    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_v / 2 - viewport_u / 2;
    point3 top_left_pixel = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    ofstream ppmFile;
    ppmFile.open("camera_viewport.ppm");
    write_ppm_header(ppmFile, image_width, image_height);
    for (int i = 0; i < image_height; i++)
    {
        clog << "\rscanlines remaining: " << (image_height - i-1) << ' ' << flush;
        for (int j = 0; j < image_width; j++)
        {
            point3 pixel_center = top_left_pixel + (j+1)  * pixel_delta_u + (i+1) * pixel_delta_v;
            vec3 ray_direction = pixel_center - camera_center;
            color pixel_color = 0.5 * color(ray_direction.x() + 1, ray_direction.y() + 1, ray_direction.z() + 1);
            write_color(ppmFile, pixel_color);
        }
    }
    clog << "Done" << endl;

 return 0;
}

color ray_color(const ray &light_ray)
{
    vec3 unit_direction = unit_vector(light_ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}