
#include "objects/Sphere.h"
#include "objects/GeoObjectList.h"
#include "utility/helper.h"
#include "utility/Vector3D.h"
#include "utility/Point3D.h"
#include "utility/Ray.h"
#include "utility/RGBPixel.h"
#include "world/Camera.h"
#include "materials/Lambertian.h"
#include "materials/Dielectric.h"
#include "materials/Metal.h"

using namespace vrt;


int main() {

    //World Setup
    GeoObjectList world;

    std::shared_ptr<Material> material_ground = make_shared<Lambertian>(RGBPixel(0.8, 0.8, 0.0));
    std::shared_ptr<Material> material_left = make_shared<Dielectric>(1.5);
    std::shared_ptr<Material> material_center = make_shared<Lambertian>(RGBPixel(0.1, 0.2, 0.5));
    std::shared_ptr<Material> material_right = make_shared<Metal>(RGBPixel(0.8, 0.6, 0.2),0.0);

    world.addObject(make_shared<Sphere>(Point3D( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.addObject(make_shared<Sphere>(Point3D( 0.0, 0.0, -1.0), 0.5, material_center));
    world.addObject(make_shared<Sphere>(Point3D(-1.0, 0.0, -1.0), 0.5, material_left));
    world.addObject(make_shared<Sphere>(Point3D(-1.0, 0.0, -1.0), -0.4, material_left));
    world.addObject(make_shared<Sphere>(Point3D( 1.0, 0.0, -1.0), 0.5, material_right));
    //Camera Setup
    Camera cam;

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