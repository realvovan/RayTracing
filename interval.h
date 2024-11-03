#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class Interval {
    public:
        double min,max;
        Interval() : min(+HUGE), max(-HUGE) {}
        Interval(double min, double max) : min(min), max(max) {}

        double size() const {
            return max - min;
        }

        bool contains(double x) {
            return min <= x && x <= max;
        }

        bool surrounds(double x) {
            return min < x && x < max;
        }

        double clamp(double x) const {
            if(x < min) return min;
            if(x > max) return max;
            return x;
        }

        static const Interval EMPTY, UNIVERSE;
};

const Interval Interval::EMPTY = Interval(+HUGE, -HUGE);
const Interval Interval::UNIVERSE = Interval(-HUGE, +HUGE);

#endif