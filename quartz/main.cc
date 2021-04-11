#include <iostream>
#include <functional>

#include <quartz/common.h>
#include <quartz/color.h>
#include <quartz/scene.h>
#include <quartz/sphere.h>
#include <quartz/camera.h>
#include <quartz/image.h>
#include <quartz/render.h>

#include <quartz/metal.h>
#include <quartz/lambertian.h>

quartz::color gradient_background(const quartz::ray &r)
{
    quartz::vec3<double> unit_direction = quartz::unit_vector(r.direction);
    // scale y component from [-1, 1] to [0, 1]
    auto t = 0.5 * (unit_direction.y + 1.0);

    // linearly blend two colors with taking t as the blending factor
    const quartz::color white(1.0, 1.0, 1.0);
    const quartz::color blue(0.5, 0.7, 1.0);

    return quartz::gradient_color(blue, white, t);
}

int main(int, char **)
{
    // Image with 16:9 aspect ratio, 225 px tall
    quartz::image_size size = quartz::get_image_size(16.0 / 9.0, // aspect ratio
                                                     225);       // image height

    // World
    quartz::scene world;
    auto material_ground = std::make_shared<quartz::lambertian>(quartz::color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<quartz::lambertian>(quartz::color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<quartz::metal>(quartz::color(0.8, 0.8, 0.8), 0.3);
    auto material_right = std::make_shared<quartz::metal>(quartz::color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<quartz::sphere>(quartz::point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<quartz::sphere>(quartz::point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<quartz::sphere>(quartz::point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<quartz::sphere>(quartz::point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    quartz::camera cam;

    quartz::ray_tracer tracer(gradient_background);

    quartz::renderer renderer_(size, world);

    int samples_per_pixel = 100;
    renderer_.render(tracer, cam, samples_per_pixel);

    quartz::ppm_image_writer writer;
    writer.write(renderer_.render_sink(), std::cout);

    std::cerr << "\nDone.\n";

    return 0;
}
