#ifndef QUARTZ_COMMON_H
#define QUARTZ_COMMON_H

#include <limits>
#include <cstdlib>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Mathemitical utility functions
inline double degress_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// random_double: returns a random real in [0, 1]
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// random_double(min, max): returns a random real in [min, max]
inline double random_double(double min, double max) {
    return min + random_double() * (max - min);
}

// clamp: returns the clamped value of x in the range [min, max]
inline double clamp(double x, double min, double max) {
    return x < min? min: x > max? max: x;
}

// Common headers
#include <quartz/vec3.h>
#include <quartz/ray.h>

#endif