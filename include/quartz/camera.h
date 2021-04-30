#ifndef QUARTZ_CAMERA_H
#define QUARTZ_CAMERA_H

#include <quartz/common.h>

namespace quartz
{
    class camera
    {
    private:
        point3 origin;
        point3 lower_left_corner;

        vec3<double> horizontal;
        vec3<double> vertical;

    public:
        camera(point3 lookfrom,
               point3 lookat,
               vec3<double> vup,
               double vfov,
               double aspect_ratio)
        {
            auto theta = degress_to_radians(vfov);
            auto h = tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;

            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - w;
        }

        ray get_ray(double s, double t) const
        {
            return ray(origin,
                       lower_left_corner +
                           s * horizontal + t * vertical - origin);
        }
    };

}

#endif