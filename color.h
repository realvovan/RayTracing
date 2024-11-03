#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "interval.h"
#include "iostream"

using Color = Vector3;

void write_color(const Color& pixel_color,std::ostream& out = std::cout) {
    static const Interval INTENSITY(0.000,0.999);
    out << int(255.999 * INTENSITY.clamp(pixel_color.x())) << ' '
    << int(255.999 * INTENSITY.clamp(pixel_color.y())) << ' '
    << int(255.999 * INTENSITY.clamp(pixel_color.z())) << '\n';
}

#endif