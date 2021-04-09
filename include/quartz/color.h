#ifndef QUARTZ_COLOR_H
#define QUARTZ_COLOR_H

#include <iostream>
#include <functional>

#include <quartz/vec3.h>
#include <quartz/hittable.h>

namespace quartz
{
    // color_int: creates a vec3<int> from color (actually a vec3<double>) to
    // be byte encodable in images.
    inline vec3<int> color_int(const color &c)
    {
        return vec3<int>(static_cast<int>(c.x * 255.999),
                         static_cast<int>(c.y * 255.999),
                         static_cast<int>(c.z * 255.999));
    }

    inline color gradient_color(quartz::color start,
                                quartz::color end,
                                double t)
    {
        return t * start + (1.0 - t) * end;
    }

    using render_background = std::function<color(const ray &)>;

    // ray_tracer: computes color for a given ray by tracing it and
    // scattering it against a hittable world.
    class ray_tracer
    {
    private:
        // background for rays that don't hit anything
        const render_background background;

    public:
        ray_tracer(render_background back) : background{back} {}

        // ray_tracer::trace(): computes the color for a traced ray
        color trace(const ray &r, const hittable &world) const
        {
            hit_record rec;
            if (world.hit(r, 0, infinity, rec))
            {
                return 0.5 * (rec.normal + quartz::color(1, 1, 1));
            }

            return background(r);
        }
    };
}

#endif