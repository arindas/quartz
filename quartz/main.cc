#include <iostream>
#include <quartz/vec3.h>
#include <quartz/color.h>
#include <quartz/ray.h>

// hit_sphere: function to determine whether a ray hits a sphere centred at the given point
// with the given radius. The equation for a point intersecting on the surface of a sphere
// is given as follows:
//      t*t * dot(b_, b_) + 2*t * dot(b, A_ - C_) + dot(A_ - C_, A_ - C_) - r*r = 0
// where
//  the ray is denoted by P(t) = A_ + dot(b_, t)
//  the sphere is centered at C_ with radius r
//
// Comparing this equation with at*T + b*t + c, i.e a quadratic equation in t, we have:
//      a = dot(b_, b_)
//      b = 2 * dot(b_, A_ - C_)
//      c = dot(A_ - C_, A_ - C_) - r*r
//
// We only need to check whether for the given coefficients for the equation in t, solutions
// exist or not. We do that by checking whether the discriminant is greater than 0.
// i.e b*b - 4*a*c > 0
bool hit_sphere(const quartz::point3 &center, double radius, const quartz::ray &r)
{
    quartz::vec3<double> oc = r.origin - center; // A_ - C_

    auto a = quartz::dot(r.direction, r.direction); // dot(b_, b_)
    auto b = 2.0 * quartz::dot(r.direction, oc);    // 2 * dot(b_, A_ - C_)
    auto c = quartz::dot(oc, oc) - radius * radius; // dot(A_ - C_, A_ - C_) - r*r

    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

// ray_color: temporary ray to color mapper for testing. Produces a blue to
// white gradient from top to bottom.
quartz::color ray_color(const quartz::ray &r)
{
    if (hit_sphere(quartz::point3(0, 0, -1), 0.5, r))
    {
        return quartz::color(1, 0, 0);
    }

    // obtain unit vector direction for given ray
    quartz::vec3<double> unit_direction = quartz::unit_vector(r.direction);

    // scale y component from [-1, 1] to [0, 1]
    double t = (unit_direction.y + 1.0) * 0.5;

    // linearly blend two colors with taking t as the blending factor
    const quartz::color white(1.0, 1.0, 1.0);
    const quartz::color blue(0.5, 0.7, 1.0);

    return (1.0 - t) * white + t * blue;
}

int main(int, char **)
{
    // Image with 16:9 aspect ratio, 400 px wide
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = quartz::point3();
    auto horizontal = quartz::vec3<double>(viewport_width, 0, 0);
    auto vertical = quartz::vec3<double>(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - quartz::vec3<double>(0, 0, focal_length);

    // Render

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            quartz::ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            quartz::color pixel_color = ray_color(r);

            quartz::write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}
