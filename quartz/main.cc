#include <iostream>
#include <quartz/vec3.h>
#include <quartz/color.h>

int main(int, char **)
{
    // Generate a PPM gradient

    const int image_rows = 256;
    const int image_cols = 256;

    std::cout << "P3" << std::endl
              << image_rows << " " << image_cols << std::endl
              << 255 << std::endl;

    for (int i{image_rows - 1}; i >= 0; --i)
    {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j{0}; j < image_cols; ++j)
        {
            quartz::color pixel_color(double(j) / (image_cols - 1),
                                      double(i) / (image_rows - 1),
                                      0.25);
            quartz::write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
