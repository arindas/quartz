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
        metal(const color &c, double f) : albedo{c}, fuzz{f} {}

        virtual bool scatter(const ray &r_in,       // incident ray
                             const hit_record &rec, // ray-surface hit details
                             color &attentuation,   // attentuation color
                             ray &scattered) const override
        {
            vec3<double> reflected = reflect(unit_vector(r_in.direction),
                                             rec.normal);

            scattered = ray(rec.p,
                            reflected + fuzz * random_double_vec3_in_unit_sphere());
            attentuation = albedo;
            return (dot(scattered.direction, rec.normal) > 0);
        }

    private:
        color albedo;
        double fuzz;
    };

} // namespace quartz

#endif