#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "interval.h"
#include "iostream"

using Color = Vector3;

inline double linear_to_gamma(double linear_component) {
    if(linear_component > 0 ) return std::sqrt(linear_component);
    return 0;
}

void write_color(const Color& pixel_color,std::ostream& out = std::cout) {
    static const Interval INTENSITY(0.000,0.999);
    out << int(255.999 * INTENSITY.clamp(linear_to_gamma(pixel_color.x()))) << ' '
    << int(255.999 * INTENSITY.clamp(linear_to_gamma(pixel_color.y()))) << ' '
    << int(255.999 * INTENSITY.clamp(linear_to_gamma(pixel_color.z()))) << '\n';
}

#endif