#ifndef QUARTZ_COLOR_H
#define QUARTZ_COLOR_H

#include <functional>
#include <vector>

#include <quartz/hittable.h>
#include <quartz/vec3.h>

namespace quartz
{
    // color_int: creates a vec3<int> from color (actually a vec3<double>) to
    // be byte encodable in images.
    inline vec3<int> color_int(const color &c)
    {
        return vec3<int>(static_cast<int>(256 * clamp(sqrt(c.x), 0, 0.999)),
                         static_cast<int>(256 * clamp(sqrt(c.y), 0, 0.999)),
                         static_cast<int>(256 * clamp(sqrt(c.z), 0, 0.999)));
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
        const int trace_depth;

    public:
        ray_tracer(render_background back, int depth = 50)
            : background{back}, trace_depth{depth} {}

        // ray_tracer::trace(): computes the color for a traced ray
        color trace(const ray &r, const hittable &world) const
        {
            double coeff = 1.0;
            hit_record rec;
            ray r_{r};

            ray &traced_ray = r_;

            int depth = trace_depth;
            while (depth-- > 0)
            {
                if (!world.hit(traced_ray, 0.001, infinity, rec))
                    break;

                // point3 target = rec.p + rec.normal +
                //                 unit_vector(
                //                     random_double_vec3_in_unit_sphere());
                point3 target = rec.p + random_in_hemisphere(rec.normal);

                coeff *= 0.5;
                traced_ray = ray(rec.p, target - rec.p);
            }

            return depth > 0 ? coeff * background(traced_ray)
                             : coeff * color(0, 0, 0);
        }
    };
}

#endif