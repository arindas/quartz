#ifndef QUARTZ_RAY_H
#define QUARTZ_RAY_H

#include <quartz/vec3.h>

namespace quartz
{
    // ray: represents a vector function of the form P_(t) = A_ + t*b_ ;
    // where A_ is the ray origin, b_ is the ray direction and t is the
    // scaling parameter, to move along the ray.
    struct ray
    {
        const point3 origin;
        const vec3<double> direction;

        ray() {}
        ray(const point3 &orig, const vec3<double> &dir)
            : origin{orig}, direction{dir} {}
        
        point3 at(double t) const {
            return origin + t * direction;
        }
    };
}

#endif