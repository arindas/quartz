#ifndef QUARTZ_METAL_H
#define QUARTZ_METAL_H

#include <quartz/vec3.h>
#include <quartz/ray.h>
#include <quartz/material.h>
#include <quartz/hittable.h>

namespace quartz
{
    class metal : public material
    {
    public:
        metal(const color &c) : albedo{c} {}

        virtual bool scatter(const ray &r_in,       // incident ray
                             const hit_record &rec, // ray-surface hit details
                             color &attentuation,   // attentuation color
                             ray &scattered) const
        {
            vec3<double> reflected = reflect(unit_vector(r_in.direction),
                                             rec.normal);

            scattered = ray(rec.p, reflected);
            attentuation = albedo;
            return (dot(scattered.direction, rec.normal) > 0);
        }

    private:
        color albedo;
    };

} // namespace quartz

#endif