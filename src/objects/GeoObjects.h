#ifndef VRT_GEO_OBJECT_H
#define VRT_GEO_OBJECT_H

#include "../utility/Point3D.h"
#include "../utility/Vector3D.h"
#include "../utility/Ray.h"
#include "../utility/helper.h"


namespace vrt {

    //class to store 
    class HitRec {
    public:
        void setFaceNormal(const Ray& ray, const Vector3D& normal);
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

    inline RGBPixel rayColor(const Ray& ray, const GeoObject& world) {
        HitRec record;
        if (world.hit(ray, 0, INF, record)) {
            RGBPixel normal = RGBPixel(record.normal_.getX(), record.normal_.getY(), record.normal_.getZ());
            return 0.5 * (normal + RGBPixel(1,1,1));
        }

        Vector3D unitDirection = unitVector(ray.getDirectionVector());
        double t = 0.5 * (unitDirection.getY() + 1.0);
        RGBPixel blendedColor = (1.0-t)*RGBPixel(1.0, 1.0, 1.0) + t*RGBPixel(0.5, 0.7, 1.0);
        return blendedColor;
    }
}

#endif
