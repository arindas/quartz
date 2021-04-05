#ifndef QUARTZ_VEC3_H
#define QUARTZ_VEC3_H

#include <iostream>
#include <cstdlib>

namespace quartz
{
    // vec3: immutable vector in R^3
    template <class T>
    struct vec3
    {
        const T x, y, z;

        vec3(T x_, T y_, T z_) : x{x_}, y{y_}, z{z_} {}

        vec3 operator-() const { return vec3(-x, -y, -z); }

        double length_squared() const { return x * x + y * y + z * z; }

        double length() const { return sqrt(length_squared()); }
    };

    template <class T>
    inline std::ostream &operator<<(std::ostream out, vec3<T> &v)
    {
        return out << v.x << " " << v.y << " " << v.z;
    }

    using point3 = vec3<double>;
    using color = vec3<double>;
};
#endif