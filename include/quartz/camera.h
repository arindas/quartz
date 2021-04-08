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
        camera()
        {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto focal_length = 1.0;
            auto viewport_width = aspect_ratio * viewport_height;
            origin = point3(0.0, 0.0, 0.0);

            horizontal = vec3<double>(viewport_width, 0.0, 0.0);
            vertical = vec3<double>(0.0, viewport_height, 0.0);

            lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - vec3<double>(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const
        {
            return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        }
    };

}

#endif