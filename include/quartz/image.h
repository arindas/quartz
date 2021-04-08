#ifndef QUARTZ_IMAGE_H
#define QUARTZ_IMAGE_H

#include <quartz/color.h>

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

    class image_writer
    {
    public:
        virtual void write_pixel(color c, int px, int py) = 0;
    };

} // namespace quartz

#endif