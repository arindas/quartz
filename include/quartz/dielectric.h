#ifndef QUARTZ_DIELECTRIC_H
#define QUARTZ_DIELECTRIC_H

#include <quartz/material.h>

namespace quartz
{
    class dielectric : public material
    {
    public:
        dielectric(double index_of_refraction)
            : ir{index_of_refraction} {}

        virtual bool scatter(const ray &r_in,       // incident ray
                             const hit_record &rec, // ray-surface hit details
                             color &attentuation,   // attentuation color
                             ray &scattered) const override
        {
            attentuation = color(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? 1.0 / ir : ir;

            vec3<double> unit_direction = unit_vector(r_in.direction);
            vec3<double> refracted = refract(unit_direction,
                                             rec.normal,
                                             refraction_ratio);

            scattered = ray(rec.p, refracted);
            return true;
        }

    private:
        double ir;
    };

} // namespace quartz

#endif