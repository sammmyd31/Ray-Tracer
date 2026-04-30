#ifndef COLOR_H
#define COLOR_H

#include "interval.hpp"
#include "vector3.hpp"

using color = vector3;

void write_color(std::ostream& out, const color& pixel_color) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

#endif