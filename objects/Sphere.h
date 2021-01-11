#ifndef VRT_SPHERE_H
#define VRT_SPHERE_H

#include "GeoObject.h"

namespace vrt {
    
    class Sphere : public GeoObject {
    public:
        Sphere();
        Sphere(Point3D cen, double rad);
        Point3D getCenter();
        double getRadius();
        bool hit(const Ray& ray, double t_min, double t_max, HitRec& record) const override;
    private:
        //sphere params
        double radius_;
        Point3D center_;
    };

    //class Methods
    Sphere::Sphere() {
        //create a generic sphere by default
        radius_ = 0.5;
        center_ = Point3D(0,0,-1);
    }

    Sphere::Sphere(const Point3D cen,double rad) : center_{cen}, radius_{rad} {
        //Empty Ctor Body
    }

    double Sphere::getRadius() {
        return radius_;
    }

    Point3D Sphere::getCenter() {
        return center_;
    }

    //hit method
    bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRec& record) const {
        //ray-sphere intersection
        //make origin vector out of the origin point
        Vector3D origin(ray.getOriginPoint().x, ray.getOriginPoint().y, ray.getOriginPoint().z);
        Vector3D center(center_.x, center_.y, center_.z);
        Vector3D OC = origin - center;
        //quadratic discriminant setup - 
        double a = ray.getDirectionVector().magSquared();
        double b = dotProduct(OC,ray.getDirectionVector());
        double c = OC.magSquared() - radius_*radius_;
        //interection checks - tangent, interect two points, no intersection 
        //simplified equation using discriminant/2
        double d = b*b - a*c;
        //finding the appropriate points in the time range
        if(d < 0) {return false;}
        double root = (-b - std::sqrt(d)) / a;
        if(root < t_min || t_max < root){
            root = (-b + std::sqrt(d)) / a;
            //check the negative root
            if(root < t_min || t_max < root){
                return false;
            }
        }

        //set the HitRecord
        record.t_ = root;
        record.point_ = ray.getPoint(record.t_);
        //determine the normal
        Point3D temp = (record.point_ - center_) / radius_; 
        Vector3D outwardNormal = Vector3D(temp.x, temp.y, temp.z);
        record.setFaceNormal(ray,outwardNormal);

        return true;   
    }

} // namespace vrt

#endif