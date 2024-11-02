#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include "cmath"
#include "iostream"
#include "limits"
#include "memory"

using std::make_shared;
using std::shared_ptr;

const double HUGE = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

//converts degrees to radians
inline double rad(double degrees) {
    return degrees * PI / 180.0;
}

#include "interval.h"
#include "vector3.h"
#include "color.h"
#include "ray.h"

#endif