#include <iostream>

#include "shapes.h"
#include "camera.h"
#include "rays.h"

using namespace RayTracer;

int main() {
   
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //viewport setup
    ShapeList world;
    world.addPointer(std::make_shared<Sphere>(Point(0,0,-1), 0.5));
    world.addPointer(std::make_shared<Sphere>(Point(0,-100.5,-1), 100));
    unique_ptr<Camera> viewer(new Camera);
    //loop for rows
    for (auto j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        //loop for pixels
        for (auto i = 0; i < image_width; i++) {
            //loop for pixel samples (within a pixel)
            Color pixelColor {0,0,0};
            for (auto s = 0; s < 100; ++s ){
                double u = (i + randomDecimal())/ (image_width-1);
                double v = (j + randomDecimal()) / (image_height-1);
                Ray rayIn = viewer->sendRay(u,v);
                pixelColor +=  rayColor(rayIn,world,maxDepth);
            }
            writeColor(std::cout, pixelColor, pixelSamples);
        }
    }

    return 0;
}
