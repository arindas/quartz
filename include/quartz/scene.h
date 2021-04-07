#ifndef QUARTZ_SCENE_H
#define QUARTZ_SCENE_H

#include <quartz/hittable.h>
#include <memory>
#include <vector>

namespace quartz
{
    class scene : public hittable
    {
    private:
        std::vector<std::shared_ptr<hittable>> hittables;

    public:
        scene() {}
        scene(std::shared_ptr<hittable> hittable_obj) { add(hittable_obj); }

        void clear() { hittables.clear(); }
        void add(std::shared_ptr<hittable> hittable_obj)
        {
            hittables.push_back(hittable_obj);
        }

        virtual bool hit(const ray &r,
                         double t_min, double t_max,
                         hit_record &rec) const override;
    };

    // scene::hit(): checks if the ray hits any hittable in the scene and updates the
    // hit_record with ray-hittable hit details for the hittable closes to the ray.
    bool scene::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        hit_record temp_rec;
        bool hit_anything{false};
        auto closest_so_far = t_max;

        for(const auto &hittable_obj: hittables) {
            if(hittable_obj->hit(r, t_min, closest_so_far, temp_rec)) {
                // there's a hittable with t within [t_min, closest_so_far]
                // We use this t as the closest_so_far(t upper-bound) for the
                // next iteration. In this manner, we minimize the upper bound
                // on t and closest_so_far satisifies it's invariants.
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec; // update hit record to correspond to the closest hit

            }
        }

        return hit_anything;
    }

} // namespace quartz

#endif