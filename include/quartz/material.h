#ifndef QUARTZ_MATERIAL_H
#define QUARTZ_MATERIAL_H

namespace quartz
{
    struct hit_record;

    // material: abstract interface to represent materials which scatter light
    class material
    {
    public:
        // bool material::scatter(...) - returns whether or not a ray was scattered, besides
        // producing information about the degree of ray attentuation and the details of the
        // scattered ray.
        virtual bool scatter(const ray &r_in,           // incident ray
                             const hit_record &rec,     // ray-surface hit details
                             color &attentuation,       // attentuation color
                             ray &scattered) const = 0; // scattered ray produced
    };

} // namespace quartz

#endif