#ifndef QUARTZ_COMMON_H
#define QUARTZ_COMMON_H

// Common headers
#include <quartz/vec3.h>
#include <quartz/ray.h>

#include <limits>
#include <cstdlib>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Mathemitical utility functions
inline double degress_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

// random_double: returns a random real in [0, 1]
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

// random_double(min, max): returns a random real in [min, max]
inline double random_double(double min, double max)
{
    return min + random_double() * (max - min);
}

inline quartz::vec3<double> random_double_vec3()
{
    return quartz::vec3<double>(random_double(),
                                random_double(),
                                random_double());
}

inline quartz::vec3<double> random_double_vec3(double min,
                                               double max)
{
    return quartz::vec3<double>(random_double(min, max),
                                random_double(min, max),
                                random_double(min, max));
}

inline quartz::vec3<double> random_double_vec3_in_unit_sphere()
{
    while (true)
    {
        quartz::vec3<double> v = random_double_vec3(-1, 1);
        if (v.length_squared() >= 1)
            continue;

        return v;
    }
}

quartz::vec3<double> random_in_hemisphere(const quartz::vec3<double> &normal)
{
    quartz::vec3<double> in_unit_sphere = random_double_vec3_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// clamp: returns the clamped value of x in the range [min, max]
inline double clamp(double x, double min, double max)
{
    return x < min ? min : x > max ? max
                                   : x;
}

inline double noisy_scale_to_0_1(int x, int max_value)
{
    return double(x + random_double()) / (max_value - 1);
}

inline bool near_zero(const quartz::vec3<double> &v)
{
    const auto s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

#endif