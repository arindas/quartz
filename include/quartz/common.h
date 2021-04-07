#ifndef QUARTZ_COMMON_H
#define QUARTZ_COMMON_H

#include <limits>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Mathemitical utility functions
inline double degress_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common headers
#include <quartz/vec3.h>
#include <quartz/ray.h>

#endif