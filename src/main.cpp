#include <iostream>

#include "helper.h"
#include "shapes.h"
#include "rays.h"

using namespace RayTracer;

int main() {
   
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //viewport setup
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspect_ratio;
    double focalLength = 1.0;
    Point origin{0,0,0};
    Vector horizontal {viewportWidth,0,0};
    Vector vertical {0,viewportHeight,0};
    Vector lower_left_corner = origin - horizontal/2 - vertical/2 - Vector{0, 0, focalLength};
    //loop for rows
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        //loop for pixels
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width-1);
            double v = double(j) / (image_height-1);
            // setup a color gradient
            Ray scene(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Color pixelColor = rayColor(scene);
            writeColor(std::cout, pixelColor);

        }
    }

    return 0;
}
