#ifndef QUARTZ_HITTABLE_H
#define QUARTZ_HITTABLE_H

#include <quartz/ray.h>

namespace quartz
{
    // hit_record: represents the details of a hit
    struct hit_record
    {
        point3 p;            // point of intersection with ray
        vec3<double> normal; // normal vector to surface
        double t;            // P(t) = A_ + t*b_
        bool front_face;     // whether or not the ray is coming
                             // towards the front_face

        // set_face_normal: sets face normal opposite the direction of ray incidence
        inline void set_face_normal(const ray& r, const vec3<double>& outward_normal) {
            front_face = dot(r.direction, outward_normal) < 0;
            normal = front_face? outward_normal: -outward_normal;
        }
    };

    // hittable: abstract interface which represents any surface or
    // volume that can be hit by a ray.
    //
    // Design decision: we take a mutable reference to a hit record
    // so that it can be mutated on the fly and reused for multiple
    // ray-hittable intersections. Returning hit records would cause
    // multiple allocations and deallocations on the stack, which
    // could have affected performance.
    class hittable
    {
    public:
        virtual bool hit(const ray &r,
                         double t_min, double t_max,
                         hit_record &rec) const = 0;
    };

}

#endif