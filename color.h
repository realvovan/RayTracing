#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"
#include "iostream"
#include "iostream"

using Color = Vector3;

void write_color(const Color& pixel_color,std::ostream& out = std::cout) {
    out << int(255.999 * pixel_color.x()) << ' '
    << int(255.999 * pixel_color.y()) << ' '
    << int(255.999 * pixel_color.z()) << '\n';
}

#endif