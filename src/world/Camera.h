#ifndef VRT_CAMERA_H
#define VRT_CAMERA_H

#include "../utility/helper.h"
#include "../utility/Point3D.h"
#include "../utility/Ray.h"
#include "../utility/Vector3D.h"

//abstraction for camera class
namespace vrt {

    //Image Size information 
    constexpr int imageWidth = 1200;
    constexpr double aspectRatio = 3.0/2.0;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    
    class Camera {
    public:
        Camera(Point3D lookFrom, Point3D lookAt, Vector3D veiwUp, double vfov, 
            double aspect_ratio, double apperature, double focusDistance);
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
        Ray getRay(double s, double t) const;
    private:
        //viewport dimensions
        Point3D origin_;
        Point3D lowerLeft_;
        Vector3D horizontal_;
        Vector3D vertical_;
        Vector3D u, v, w;
        double lensRadius;
    };

    Camera::Camera (Point3D lookFrom, Point3D lookAt, Vector3D veiwUp, double vfov, 
        double aspect_ratio, double aperture, double focusDistance) {
        //camera setup
        double theta = radians(vfov);
        double h = std::tan(theta/2);
        //Camera Size Information   
        double viewportHeight = 2.0 * h;
        double viewportWidth = aspect_ratio * viewportHeight;
        
        w = unitVector(Vector3D((lookFrom.x - lookAt.x),(lookFrom.y - lookAt.y),(lookFrom.z - lookAt.z)));
        u = unitVector(crossProduct(veiwUp,w));
        v = crossProduct(w,u);

        origin_ = lookFrom;
        horizontal_ = focusDistance * viewportWidth * u;
        vertical_ = focusDistance * viewportHeight * v;
        lowerLeft_ =  origin_ - horizontal_.toPoint()/2 - vertical_.toPoint()/2 - focusDistance * w.toPoint();

        lensRadius = aperture / 2;
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

    Ray Camera::getRay(double s, double t) const {
        //helper methods
        Vector3D rd = lensRadius * randomInUnitDisk();
        Vector3D offset = u * rd.getX() + v * rd.getY();
        Vector3D lowLeft(lowerLeft_.x, lowerLeft_.y, lowerLeft_.z);
        Vector3D originVec(origin_.x, origin_.y, origin_.z);
        return Ray(origin_ + offset.toPoint(), lowLeft + s*horizontal_ + t*vertical_ - originVec - offset);
    }
};

#endif