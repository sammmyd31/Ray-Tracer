#ifndef COLOR_H
#define COLOR_H

#include "vector3.hpp"

using color = vector3;

void write_color(std::ostream& out, const color& pixel_color) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    int rbyte = int(r * 255.999);
    int gbyte = int(g * 255.999);
    int bbyte = int(b * 255.999);

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

#endif