#ifndef QUARTZ_LAMBERTIAN_H
#define QUARTZ_LAMBERTIAN_H

#include <quartz/material.h>
#include <quartz/common.h>
#include <quartz/hittable.h>

namespace quartz
{
    class lambertian : public material
    {
    public:
        lambertian(const color &a) : albedo{a} {}

        virtual bool scatter(const ray &r_in,       // incident ray
                             const hit_record &rec, // ray-surface hit details
                             color &attentuation,   // attentuation color
                             ray &scattered) const override
        {
            auto scatter_direction = rec.normal +
                                     unit_vector(
                                         random_double_vec3_in_unit_sphere());

            if (near_zero(scatter_direction))
            {
                scatter_direction = rec.normal;
            }

            scattered = ray(rec.p, scatter_direction);
            attentuation = albedo;

            return true;
        }

    private:
        color albedo;
    };

} // namespace quartz

#endif