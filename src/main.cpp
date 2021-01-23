#include "Raytracer.h"

int main() {

    //World Setup
    GeoObjectList world = randomScene();

    Point3D lookFrom(13,2,3);
    Point3D lookAt(0,0,0);
    Vector3D viewUp(0,1,0);
    double focusDist = 10.0;
    double aperture = 0.1;

    Camera cam(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture,focusDist);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    //Image Renderng
    for(int j = imageHeight-1; j >= 0; j--){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < imageWidth; i++) {
            RGBPixel pixel(0,0,0);  //default (0,0,0)
            for(int s = 0; s < pixelSamples; ++s) {
                double u = (i + randomDouble()) / (imageWidth-1);
                double v = (j + randomDouble()) / (imageHeight-1);
                const Ray& r = cam.getRay(u, v);
                pixel += rayColor(r, world, maxDepth);
            }
            //write the pixel
            std::cout<<pixel<<std::endl;
        }
    }

    std::cerr << "\nDone.\n";
    return 0; 
}