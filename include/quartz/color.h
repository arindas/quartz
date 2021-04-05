#ifndef QUARTZ_COLOR_H
#define QUARTZ_COLOR_H

#include <iostream>
#include <quartz/vec3.h>

namespace quartz
{
    void write_color(std::ostream &out, color &pixel_color)
    {
        // write the translated value in [0, 255] for each color component
        out << static_cast<int>(pixel_color.x * 255.999) << " "
            << static_cast<int>(pixel_color.y * 255.999) << " "
            << static_cast<int>(pixel_color.z * 255.999) << "\n";
    }
}

#endif