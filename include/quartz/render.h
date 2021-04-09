#ifndef QUARTZ_RENDER_H
#define QUARTZ_RENDER_H

#include <quartz/image.h>
#include <quartz/camera.h>

namespace quartz
{
    class renderer
    {
    private:
        const hittable &world;
        image_sink sink;

    public:
        renderer(image_size size, const hittable &w)
            : sink{image_sink(size)}, world{w} {}

        const image_sink &render_sink() const { return sink; }

        const image_sink &render(const ray_tracer &tracer,
                                 const camera &cam,
                                 int samples_per_pixel);
    };

    const image_sink &renderer::render(const ray_tracer &tracer,
                                       const camera &cam,
                                       int samples_per_pixel)
    {
        for (int j = sink.size.image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
            for (int i = 0; i < sink.size.image_width; i++)
            {
                quartz::color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; s++)
                {
                    auto u = noisy_scale_to_0_1(i, sink.size.image_width);
                    auto v = noisy_scale_to_0_1(j, sink.size.image_height);

                    quartz::ray r = cam.get_ray(u, v);
                    pixel_color += tracer.trace(r, world);
                }

                pixel_color /= static_cast<double>(samples_per_pixel);

                int px = i, py = sink.size.image_height - j - 1;
                sink.write_pixel(pixel_color, px, py);
            }
        }

        std::cerr << "\nDone rendering to image sink.\n";

        return render_sink();
    }

} // namespace quartz

#endif