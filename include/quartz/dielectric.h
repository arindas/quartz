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
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool will_not_refract = (refraction_ratio * sin_theta > 1.0) ||
                                    (reflectance(cos_theta, refraction_ratio) >
                                     random_double());
            vec3<double> direction = will_not_refract ? reflect(unit_direction,
                                                                rec.normal)
                                                      : refract(unit_direction,
                                                                rec.normal,
                                                                refraction_ratio);

            scattered = ray(rec.p, direction);
            return true;
        }

    private:
        double ir;

        static double reflectance(double cosine, double ref_idx)
        {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
    };

} // namespace quartz

#endif