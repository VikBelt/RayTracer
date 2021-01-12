#ifndef VRT_GEO_OBJECT_H
#define VRT_GEO_OBJECT_H

#include <memory>
#include "../materials/material.h"
#include "../utility/Point3D.h"
#include "../utility/Vector3D.h"
#include "../utility/Ray.h"
#include "../utility/helper.h"

namespace vrt {

    class Material;

    class HitRec {
    public:
        void setFaceNormal(const Ray& ray, const Vector3D& normal);
        std::shared_ptr<Material> material_;
        Point3D point_;
        Vector3D normal_;
        bool frontFace_;
        double t_;
    };

    //interface for an any object that a ray can hit
    class GeoObject {
    public:
        virtual bool hit(const Ray& ray, double t_min, double t_max, HitRec& record) const = 0;
    };

    //HitRec Methods
    void HitRec::setFaceNormal(const Ray& ray, const Vector3D& normal)  {
        //compare the directions 
        if(dotProduct(ray.getDirectionVector(),normal) > 0) {
            //back fact since the ray and outward normal dotted is positive
            frontFace_ = false;
            normal_ = -normal;
        } else {
            //front face since directions horizontal component is negative 
            frontFace_ = true;
            normal_ = normal;
        }
    }

    RGBPixel rayColor(const Ray& ray, const GeoObject& world, int depth) {
        HitRec record;

        //recursive base-case
        if (depth <= 0) {
            return RGBPixel(0,0,0);
        }

        if (world.hit(ray, 0.001, INF, record)) {
            Ray scattered;
            RGBPixel attenuation;
            if(record.material_->scatteredRay(ray, record, attenuation, scattered))
                return attenuation * rayColor(scattered, world, depth-1);
                
            return RGBPixel(0,0,0);
        }

        Vector3D unitDirection = unitVector(ray.getDirectionVector());
        double t = 0.5 * (unitDirection.getY() + 1.0);
        RGBPixel blendedColor = (1.0-t)*RGBPixel(1.0, 1.0, 1.0) + t*RGBPixel(0.5, 0.7, 1.0);
        return blendedColor;
    }
}

#endif