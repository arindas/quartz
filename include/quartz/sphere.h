#ifndef QUARTZ_SPHERE_H
#define QUARTZ_SPHERE_H

#include <quartz/hittable.h>

namespace quartz
{
    class sphere : public hittable
    {
    private:
        point3 center;
        double radius;
        std::shared_ptr<material> mat_ptr;

    public:
        sphere() {}
        sphere(point3 cen, double r, std::shared_ptr<material> m)
            : center{cen}, radius{r}, mat_ptr{m} {}

        virtual bool hit(const ray &r,
                         double t_min, double t_max,
                         hit_record &rec) const override;
    };

    // sphere::hit(): function to determine whether a ray hits a sphere centred at the given point
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
    //
    // The formula can be simplified further as follows:
    //      t = (-b [+ -] sqrt(b*b - 4*a*c)) / (2*a)
    //
    // Let half_b = b / 2 = dot(b_, A_ - C_). Substituting b = 2 * half_b in the above stmt.:
    //      t = (-2.0*half_b [+ -] sqrt(4*half_b*half_b - 4*a*c)) / (2*a)
    //      t = (-2.0*half_b [+ -] sqrt(4*half_b*half_b - 4*a*c)) / (2*a)
    //      t = (-half_b [+ -] sqrt(half_b*half_b - a*c)) / a
    //
    // Hence instead of computing the discriminant, we compute half_b*half_b - a*c for checking
    // the existence and values of roots.
    bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        quartz::vec3<double> oc = r.origin - center; // A_ - C_

        // dot(x_, x_) = x_.length_squared()

        auto a = r.direction.length_squared();          // dot(b_, b_)
        auto half_b = quartz::dot(r.direction, oc);     // dot(b_, A_ - C_)
        auto c = oc.length_squared() - radius * radius; // dot(A_ - C_, A_ - C_) - r*r
        auto discriminant = half_b * half_b - a * c;

        if (discriminant < 0)
            return false;

        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || root > t_max)
        {
            root = (-half_b + sqrtd) / a;

            if (root < t_min || root > t_max)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3<double> outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;

        return true;
    }
} // namespace quartz

#endif
