#ifndef VRT_CAMERA_H
#define VRT_CAMERA_H

#include "../utility/helper.h"
#include "../utility/Point3D.h"
#include "../utility/Ray.h"
#include "../utility/Vector3D.h"

//abstraction for camera class
namespace vrt {

    //Image Size information 
    constexpr int imageWidth = 600;
    constexpr double aspectRatio = 16.0/9.0;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    
    //Camera Size Information
    constexpr double viewportHeight = 2.0;
    constexpr double viewportWidth = aspectRatio * viewportHeight;
    constexpr double focalLength = 1.0;

    class Camera {
    public:
        Camera();
        //getter methods
        Point3D getOrigin();
        Point3D getOrigin() const;
        Point3D getLowerLeft();
        Point3D getLowerLeft() const;
        Vector3D getHorizontal();
        Vector3D getHorizontal() const;
        Vector3D getVertical(); 
        Vector3D getVertical() const;
        //get ray 
        Ray getRay(double u, double v) const;
    private:
        //viewport dimensions
        Point3D origin_;
        Point3D lowerLeft_;
        Vector3D horizontal_;
        Vector3D vertical_;
    };

    Camera::Camera() {
        origin_ = Point3D(0,0,0);
        horizontal_ = Vector3D(viewportWidth, 0, 0);
        vertical_ = Vector3D(0.0, viewportHeight, 0.0);
        lowerLeft_ =  origin_ - horizontal_.toPoint()/2 - vertical_.toPoint()/2 - Vector3D(0, 0, focalLength).toPoint();
    }

    Point3D Camera::getOrigin() {
        return origin_;
    }

    Point3D Camera::getOrigin() const {
        return origin_;
    }

    Point3D Camera::getLowerLeft() {
        return lowerLeft_;
    }

    Point3D Camera::getLowerLeft() const {
        return lowerLeft_;
    }

    Vector3D Camera::getHorizontal() {
        return horizontal_;
    }

    Vector3D Camera::getHorizontal() const {
        return horizontal_;
    }

    Vector3D Camera::getVertical() {
        return vertical_;
    }

    Vector3D Camera::getVertical() const {
        return vertical_;
    }

    Ray Camera::getRay(double u, double v) const {
        //helper methods
        Vector3D  lowLeft(lowerLeft_.x,lowerLeft_.y,lowerLeft_.z);
        Vector3D originVec(origin_.x,origin_.y,origin_.z);
        Ray newRay(origin_, lowLeft + u*horizontal_ + v*vertical_ - originVec);
        return newRay;
    }
};

#endif