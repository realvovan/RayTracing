#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include "cmath"
#include "cstdlib"
#include "iostream"
#include "limits"
#include "memory"

using std::make_shared;
using std::shared_ptr;

const double HUGE = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

//Converts degrees to radians
inline double rad(double degrees) {
    return degrees * PI / 180.0;
}

//Returns a random real in [0,1)
inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

//Returns a random real in [min,max)
//@param min: inclusive minimum of a possible random number
//@param max: exclusive maximum of a possible random number
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#include "interval.h"
#include "vector3.h"
#include "color.h"
#include "ray.h"

#endif