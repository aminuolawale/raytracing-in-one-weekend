#include <iostream>
#include "02.vec3.h"
#include "05.ray.h"
#include "03.color.h"
#include <fstream>

color ray_color(const ray &light_ray);

int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height > 0 ? image_height : 1;

    /*
   not using aspect ratio because height is rounded down and can't be less than 1
   causing the aspect ratio be out of sync. This is the actual aspect ratio

    */

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * static_cast<double>(image_width / image_height);
    point3 camera_center = point3(0, 0, 0);

    // Pixel grid vectors
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);
    vec3 pixel_delta_u = unit_vector(viewport_u);
    vec3 pixel_delta_v = unit_vector(viewport_v);

    //-
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; // I still don't agree with this
    point3 top_left_pixel = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::ofstream ppmFile;
    ppmFile.open("first_render.ppm");
    ppmFile << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i)
    {
        std::clog << "\rscanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j)
        {
            point3 pixel_center = top_left_pixel + j * pixel_delta_u + i * pixel_delta_v;
            vec3 ray_direction = unit_vector(pixel_center - camera_center);
            ray light_ray(camera_center, ray_direction);
            color pixel_color = ray_color(light_ray);
            write_color(ppmFile, pixel_color);
        }
    }
    std::clog << "Done" << std::endl;
}

color ray_color(const ray &light_ray)
{
    vec3 unit_v = unit_vector(light_ray.direction());
    double a = 0.5 * (unit_v.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(.5, .7, 1.0);
}