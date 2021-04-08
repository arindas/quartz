#include <iostream>
#include <functional>

#include <quartz/common.h>
#include <quartz/color.h>
#include <quartz/scene.h>
#include <quartz/sphere.h>
#include <quartz/camera.h>

// gradient_color: maps t to a linearly interpolated color, t is expected to be [-1, 1]
quartz::color gradient_color(quartz::color start, quartz::color end, double t)
{
    return t * start + (1.0 - t) * end;
}

quartz::color gradient_background(const quartz::ray &r)
{
    quartz::vec3<double> unit_direction = quartz::unit_vector(r.direction);
    // scale y component from [-1, 1] to [0, 1]
    auto t = 0.5 * (unit_direction.y + 1.0);

    // linearly blend two colors with taking t as the blending factor
    const quartz::color white(1.0, 1.0, 1.0);
    const quartz::color blue(0.5, 0.7, 1.0);

    return gradient_color(blue, white, t);
}

// ray_color: hits the ray with the given hittable and computes the color
quartz::color ray_color(const quartz::ray &r,
                        const quartz::hittable &world,
                        std::function<quartz::color(const quartz::ray &)> background)
{
    quartz::hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + quartz::color(1, 1, 1));
    }

    return background(r);
}

int main(int, char **)
{
    // Image with 16:9 aspect ratio, 400 px wide
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 100;

    // World
    quartz::scene world;
    world.add(std::make_shared<quartz::sphere>(quartz::point3(0, 0, -1), 0.5));
    world.add(std::make_shared<quartz::sphere>(quartz::point3(0, -100.5, -1), 100));

    // Camera
    quartz::camera cam;

    // Render

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            quartz::color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = double(i + random_double()) / (image_width - 1);
                auto v = double(j + random_double()) / (image_height - 1);

                quartz::ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, gradient_background);
            }

            pixel_color /= static_cast<double>(samples_per_pixel);
            quartz::write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}
