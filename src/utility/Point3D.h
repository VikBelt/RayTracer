#ifndef VRT_POINT3D_H
#define VRT_POINT3D_H

#include <iostream>

namespace vrt {

    class Point3D {
    public:
        Point3D();
        Point3D(double x_pos, double y_pos, double z_pos);
        bool operator== (const Point3D& other);
        bool operator!= (const Point3D& other);
        Point3D& operator+=(const Point3D& other);
        Point3D& operator*=(const Point3D& other);
        double x;
        double y;
        double z;
    };

    //class methods
    Point3D::Point3D() : x{0},y{0},z{0} {
        //Empty Body
    }

    Point3D::Point3D(double x_pos, double y_pos, double z_pos) : x{x_pos}, y{y_pos}, z{z_pos} {
        //Empty Body
    }

    bool Point3D::operator== (const Point3D& other){

        if(x != other.x || y != other.y || z != other.z) {
            return false;
        }

        return true;
    }

    bool Point3D::operator!= (const Point3D& other){
        return !(*this == other);
    }

    Point3D& Point3D::operator+= (const Point3D& other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Point3D& Point3D::operator*= (const Point3D& other){
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    //operator overloading
    inline Point3D operator+ (const Point3D& pointOne, const Point3D& pointTwo){
        return Point3D(pointOne.x + pointTwo.x, pointOne.y + pointTwo.y, pointOne.z + pointTwo.z);
    }

    inline Point3D operator- (const Point3D& pointOne, const Point3D& pointTwo){
        return Point3D(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y, pointOne.z - pointTwo.z);
    }

    inline Point3D operator* (const Point3D& pointOne, const Point3D& pointTwo){
        return Point3D(pointOne.x * pointTwo.x, pointOne.y * pointTwo.y, pointOne.z * pointTwo.z);
    }

    inline Point3D operator* (const Point3D& point, double a){
        return Point3D(a * point.x, a * point.y, a * point.z);
    }

    inline Point3D operator* (double a, const Point3D& point){
        return Point3D(a * point.x, a * point.y, a * point.z);
    }

    inline Point3D operator/ (const Point3D& point, double a){
        return Point3D(point.x / a, point.y / a, point.z / a);
    }

    inline std::ostream& operator<< (std::ostream& os, const Point3D& point) {
        os << point.x << " " << point.y << " " << point.z;
        return os;
    }

} //namespace vrt

#endif
