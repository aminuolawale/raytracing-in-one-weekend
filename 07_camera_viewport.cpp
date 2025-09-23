#include <iostream>
#include <fstream>
#include "02_vec3.h"
#include "03_color.h"
#include "06_ray.h"
#include "05_ppm_file_writer.h"
#include "08_sphere.h"

using namespace std;


color ray_color(const ray &light_ray);

color ray_color_sphere(const ray &light_ray);

bool hit_sphere(const sphere &sphere, const ray &light_ray);


int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;
    double actual_aspect_ratio = double(image_width) / image_height;

    double viewport_height = 2.0;
    double viewport_width = viewport_height * actual_aspect_ratio;

    // Distance between the camera and the viewport plane in 3D space.
    double focal_length = 1.0;
    point3 camera_center = point3();

    // Pixel grid vectors
    vec3 viewport_u = vec3(viewport_width, 0, 0);   // Row vector from the top left corner rightwards.
    vec3 viewport_v = vec3(0, -viewport_height, 0); // Column vector from the top left corner downwards.
    vec3 pixel_delta_u = viewport_u/ image_width;
    vec3 pixel_delta_v = viewport_v/image_height;

    // Remember, due to the right-handed coordinate system, the viewport in the -Z direction from the camera. 
    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_v / 2 - viewport_u / 2;
    point3 top_left_pixel = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    ofstream ppmFile;
    ppmFile.open("camera_viewport.ppm");
    write_ppm_header(ppmFile, image_width, image_height);
    for (int i = 0; i < image_height; i++)
    {
        clog << "\rscanlines remaining: " << (image_height - i) << ' ' << flush;
        for (int j = 0; j < image_width; j++)
        {
            point3 pixel_center = top_left_pixel + (j * pixel_delta_u) + (i * pixel_delta_v);
            // Vector pointing to the pixel from the camera. 
            vec3 ray_direction = pixel_center - camera_center;
            // Remember, a ray is defined by its origin and direction vector.
            ray light_ray = ray(camera_center, ray_direction);
            color pixel_color = ray_color(light_ray);
            write_color(ppmFile, pixel_color);
        }
    }
    clog << "Done" << endl;

    return 0;
}

color ray_color(const ray &light_ray)
{
    vec3 unit_direction = unit_vector(light_ray.origin());
    double t = 0.5 * (unit_direction.y() + 1.0);
    // Linear blend the colours.
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_sphere(const ray &light_ray) {
    sphere sphere;
    sphere.centre = point3(0, 0, -1) ;
    sphere.radius = 0.5;
    if (hit_sphere(sphere, light_ray)){
        // do something.
        return color(1, 0, 0); // red color;
    }
    return ray_color(light_ray);
}

bool hit_sphere(const sphere &sphere, const ray &light_ray) {
    vec3 origin_to_centre = sphere.centre  - light_ray.origin();
    double a  = dot(light_ray.direction(), light_ray.direction());
    double b = -2 * dot(light_ray.direction(), origin_to_centre);
    double c = dot(origin_to_centre, origin_to_centre) - (sphere.radius * sphere.radius);
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        cout << discriminant << endl;
    }
    return discriminant >=0;

}