#ifndef QUARTZ_IMAGE_H
#define QUARTZ_IMAGE_H

#include <quartz/color.h>
#include <quartz/vec3.h>
#include <iostream>
#include <vector>

namespace quartz
{
    struct image_size
    {
        int image_height, image_width;
        image_size(int h, int w) : image_height{h}, image_width{w} {}
    };

    image_size get_image_size(double aspect_ratio, int image_height)
    {
        return image_size(image_height,
                          static_cast<int>(aspect_ratio * image_height));
    }

    struct image_sink
    {
        std::vector<color> buffer;
        image_size size;

        image_sink(const image_size &sz)
            : size{sz},
              buffer{std::vector<color>(sz.image_height * sz.image_width)} {}

        void write_pixel(const color &c, int px, int py)
        {
            buffer[py * size.image_width + px] = c;
        }
    };

    class image_writer
    {
    public:
        virtual void write(const image_sink &sink,
                           std::ostream &out) = 0;
    };

    class ppm_image_writer : public image_writer
    {
    public:
        virtual void write(const image_sink &sink,
                           std::ostream &out) override;
    };

    void ppm_image_writer::write(const image_sink &sink, std::ostream &out)
    {
        std::cout << "P3\n"
                  << sink.size.image_width << " "
                  << sink.size.image_height << "\n255\n";

        for (auto &color : sink.buffer)
        {
            vec3<int> c = color_int(color);
            out << c << "\n";
        }
    }
} // namespace quartz

#endif