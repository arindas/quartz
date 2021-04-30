#ifndef QUARTZ_VEC3_H
#define QUARTZ_VEC3_H

#include <iostream>
#include <cmath>

namespace quartz
{
    // vec3: immutable vector in R^3
    template <class T>
    struct vec3
    {
        T x, y, z;

        vec3() : x{0}, y{0}, z{0} {}
        vec3(T x_, T y_, T z_) : x{x_}, y{y_}, z{z_} {}

        vec3 operator-() const { return vec3(-x, -y, -z); }

        double length_squared() const { return x * x + y * y + z * z; }

        double length() const { return sqrt(length_squared()); }

        vec3 &operator+=(const vec3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        vec3 &operator*=(const vec3 &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        vec3 &operator*=(T t)
        {
            x *= t;
            y *= t;
            z *= t;
            return *this;
        }

        vec3 &operator/=(T t) { return *this *= 1 / t; }
    };

    template <class T>
    inline std::ostream &operator<<(std::ostream &out, vec3<T> &v)
    {
        return out << v.x << " " << v.y << " " << v.z;
    }

    template <class T>
    inline vec3<T> operator+(const vec3<T> &u, const vec3<T> &v)
    {
        return vec3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
    }

    template <class T>
    inline vec3<T> operator-(const vec3<T> &u, const vec3<T> &v)
    {
        return vec3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
    }

    template <class T>
    inline vec3<T> operator*(const vec3<T> &u, const vec3<T> &v)
    {
        return vec3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    template <class T>
    inline vec3<T> operator*(const vec3<T> &u, T t)
    {
        return vec3<T>(u.x * t, u.y * t, u.z * t);
    }

    template <class T>
    inline vec3<T> operator*(T t, const vec3<T> &u)
    {
        return u * t;
    }

    template <class T>
    inline vec3<T> operator/(const vec3<T> &u, T t)
    {
        return (1.0 / t) * u;
    }

    template <class T>
    inline T dot(const vec3<T> &u, const vec3<T> &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    template <class T>
    inline vec3<T> cross(const vec3<T> &u, const vec3<T> &v)
    {
        return vec3<T>(u.y * v.z - u.z * v.y,
                       u.z * v.x - u.x * v.z,
                       u.x * v.y - u.y * v.x);
    }

    template <class T>
    inline vec3<T> unit_vector(const vec3<T> u)
    {
        return u / u.length();
    }

    template <class T>
    inline vec3<T> reflect(const vec3<T> &v, const vec3<T> &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    template <class T>
    inline vec3<T> refract(const vec3<T> &uv, const vec3<T> &n, double etai_over_etat) {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        vec3<T> r_out_perp = etai_over_etat * (uv + cos_theta*n);
        vec3<T> r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    using point3 = vec3<double>;
    using color = vec3<double>;
};

#endif