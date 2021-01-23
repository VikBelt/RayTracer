#ifndef RAYTRACER_H
#define RAYTRACER_H


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


//SCENE RENDERINGS

//book cover
GeoObjectList randomScene() {
    GeoObjectList world;

    shared_ptr<Material> ground = make_shared<Lambertian>(RGBPixel(0.5, 0.5, 0.5));
    world.addObject(make_shared<Sphere>(Point3D(0,-1000,0), 1000, ground));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = randomDouble();
            Point3D center(a + 0.9*randomDouble(), 0.2, b + 0.9*randomDouble());
            Point3D diffp = center - Point3D(4, 0.2, 0);
            Vector3D diff(diffp.x, diffp.y, diffp.z);

            if ( diff.magnitude() > 0.9) {
                shared_ptr<Material> sphereMat;

                if (choose_mat < 0.8) {
                    // diffuse
                    RGBPixel albedo = RGBPixel::randomColor() * RGBPixel::randomColor();
                    sphereMat = make_shared<Lambertian>(albedo);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMat));
                } else if (choose_mat < 0.95) {
                    // metal
                    RGBPixel albedo = RGBPixel::randomColor(0.5,1);
                    double fuzz = randomDouble(0, 0.5);
                    sphereMat = make_shared<Metal>(albedo, fuzz);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMat));
                } else {
                    // glass
                    sphereMat = make_shared<Dielectric>(1.5);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMat));
                }
            }
        }
    }

    shared_ptr<Material> material1 = make_shared<Dielectric>(1.5);
    world.addObject(make_shared<Sphere>(Point3D(0, 1, 0), 1.0, material1));

    shared_ptr<Material> material2 = make_shared<Lambertian>(RGBPixel(0.4, 0.2, 0.1));
    world.addObject(make_shared<Sphere>(Point3D(-4, 1, 0), 1.0, material2));

    shared_ptr<Material> material3 = make_shared<Metal>(RGBPixel(0.7, 0.6, 0.5), 0.0);
    world.addObject(make_shared<Sphere>(Point3D(4, 1, 0), 1.0, material3));

    return world;
}

#endif