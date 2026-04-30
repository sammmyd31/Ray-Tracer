#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.hpp"

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        
        std::clog << "\rDone.                 \n";
    }
private:
    int image_height;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vector3 pixel_delta_u;
    vector3 pixel_delta_v;

    void initialize() {
        image_height = std::max(int(image_width / aspect_ratio), 1);

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        double focal_length = 1.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        vector3 viewport_u = vector3(viewport_width, 0, 0);
        vector3 viewport_v = vector3(0, -viewport_height, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        vector3 viewport_upper_left = center -
                                      vector3(0, 0, focal_length) -
                                      viewport_u/2 -
                                      viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        vector3 offset = sample_square();
        point3 pixel_sample = pixel00_loc +
                              ((i + offset.x()) * pixel_delta_u) +
                              ((j + offset.y()) * pixel_delta_v);
        
        point3 ray_origin = center;
        vector3 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vector3 sample_square() const {
        return vector3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) {
            return color(0, 0, 0);
        }

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            vector3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
        }

        vector3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif