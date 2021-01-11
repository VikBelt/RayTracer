
#include "objects/Sphere.h"
#include "objects/GeoObjectList.h"
#include "utility/helper.h"
#include "utility/Vector3D.h"
#include "utility/Point3D.h"
#include "utility/Ray.h"
#include "utility/RGBPixel.h"

using namespace vrt;

int main() {

    //Image Setup
    const int width = 400;
    const double aspectRatio = 16.0/9.0;
    const int height = static_cast<int>(width / aspectRatio);

    //World Setup
    GeoObjectList world;
    //small sphere at the center of xy-plane
    world.addObject(make_shared<Sphere>(Point3D(0,0,-1),0.5));
    //large sphere at the lower part of the image
    world.addObject(make_shared<Sphere>(Point3D(0,-100.5,-1),100));

    //Camera Setup
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;
    Point3D origin = Point3D(0, 0, 0);
    Vector3D horizontal = Vector3D(viewportWidth, 0, 0);
    Vector3D vertical = Vector3D(0, viewportHeight, 0);
    Point3D lowerLeftCorner = origin - horizontal.toPoint()/2 - vertical.toPoint()/2 - Vector3D(0, 0, focalLength).toPoint();

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    //Image Renderng
    for(int j = height-1; j >= 0; j--){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < width; i++) {
            //create a color and output it
            double u = static_cast<double>(i)/(width-1);
            double v = static_cast<double>(j)/(height-1);
            Vector3D  newVec(lowerLeftCorner.x,lowerLeftCorner.y,lowerLeftCorner.z);
            Vector3D originVec(origin.x,origin.y,origin.z);
            Ray newRay(origin, newVec + u*horizontal + v*vertical - originVec);
            RGBPixel pixel = vrt::rayColor(newRay,world);
            std::cout<<pixel<<std::endl;
        }
    }

    std::cerr << "\nDone.\n";
    return 0; 
}