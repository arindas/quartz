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
        vec3<double> u, v, w;

        double lens_radius;

    public:
        camera(point3 lookfrom,
               point3 lookat,
               vec3<double> vup,
               double vfov,
               double aspect_ratio,
               double aperture,
               double focus_dist)
        {
            auto theta = degress_to_radians(vfov);
            auto h = tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin -
                                horizontal / 2.0 -
                                vertical / 2.0 -
                                focus_dist * w;

            lens_radius = aperture / 2;
        }

        ray get_ray(double s, double t) const
        {
            vec3<double> rd = lens_radius * random_in_unit_disk();
            vec3<double> offset = u * rd.x + v * rd.y;

            return ray(origin + offset,
                       lower_left_corner +
                           s * horizontal + t * vertical -
                           origin - offset);
        }
    };

}

#endif