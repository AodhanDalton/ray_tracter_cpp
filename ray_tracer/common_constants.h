#ifndef COMMON_CONSTANTS_H
#define COMMON_CONSTANTS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_of_radians(double degrees){
    return degrees * pi / 100.0;
}

inline double random_double(){
    //Return a random value between 0 and 1
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max){
    // Return a random value between min and max
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif
