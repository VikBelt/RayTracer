#ifndef VRT_RAY_H
#define VRT_RAY_H

#include "Vector3D.h"
#include "Point3D.h"
#include "RGBPixel.h"

namespace vrt{

    class Ray {
    public:
        Ray();
        Ray(const Point3D& origin, const Vector3D& direction);
        Point3D getOriginPoint();
        Vector3D getDirectionVector();
        Point3D getOriginPoint() const;
        Vector3D getDirectionVector() const;
        Point3D getPoint(double time);
    private:
        Point3D origin_;
        Vector3D direction_;
    };

    //class member functions
    Ray::Ray() {}

    Ray::Ray(const Point3D& origin, const Vector3D& direction) : 
        origin_{origin}, direction_{direction} {}
    
    Point3D Ray::getOriginPoint() {
        return origin_;
    }

    Vector3D Ray::getDirectionVector() {
        return direction_;
    }

    Point3D Ray::getOriginPoint() const {
        return origin_;
    }

    Vector3D Ray::getDirectionVector() const {
        return direction_;
    }

    Point3D Ray::getPoint(double time) {
        Point3D result = origin_ + time * direction_.toPoint();
        return result;
    }

    inline RGBPixel rayColor(const Ray& ray) {
        Vector3D unitDirection = unitVector(ray.getDirectionVector());
        double t = 0.5 * (unitDirection.getY() + 1.0);
        RGBPixel blendedColor = (1.0-t)*RGBPixel(1.0, 1.0, 1.0) + t*RGBPixel(0.5, 0.7, 1.0);
        return blendedColor;
    }

} // namespace vrt

#endif