#ifndef VRT_POINT2D_H
#define VRT_POINT2D_H

#include <iostream>
#include "Point3D.h"

namespace vrt {

    class Point2D {
    public:
        Point2D();
        Point2D(double x_pos, double y_pos);
        bool operator== (const Point2D& other);
        bool operator!= (const Point2D& other);
        Point2D& operator+=(const Point2D& other);
        Point2D& operator*=(const Point2D& other);
        Point3D toPoint3D();
        Point3D toPoint3D() const;
        double x;
        double y;
    };

    //class methods
    Point2D::Point2D() : x{0},y{0} {
        //Empty Body
    }

    Point2D::Point2D(double x_pos, double y_pos) : x{x_pos}, y{y_pos} {
        //Empty Body
    }

    bool Point2D::operator== (const Point2D& other){

        if(x != other.x || y != other.y ) {
            return false;
        }

        return true;
    }

    bool Point2D::operator!= (const Point2D& other){
        return !(*this == other);
    }

    Point2D& Point2D::operator+= (const Point2D& other){
        x += other.x;
        y += other.y;
        return *this;
    }

    Point2D& Point2D::operator*= (const Point2D& other){
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Point3D Point2D::toPoint3D() {
        return Point3D(x,y,0);
    }

    Point3D Point2D::toPoint3D() const {
        return Point3D(x,y,0);
    }

    //operator overloading
    inline Point2D operator+ (const Point2D& pointOne, const Point2D& pointTwo){
        return Point2D(pointOne.x + pointTwo.x, pointOne.y + pointTwo.y);
    }

    inline Point2D operator- (const Point2D& pointOne, const Point2D& pointTwo){
        return Point2D(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y);
    }

    inline Point2D operator* (const Point2D& pointOne, const Point2D& pointTwo){
        return Point2D(pointOne.x * pointTwo.x, pointOne.y * pointTwo.y);
    }

    inline Point2D operator* (const Point2D& point, double a){
        return Point2D(a * point.x, a * point.y);
    }

    inline Point2D operator* (double a, const Point2D& point){
        return Point2D(a * point.x, a * point.y);
    }

    inline Point2D operator/ (const Point2D& point, double a){
        return Point2D(point.x / a, point.y / a);
    }

    inline std::ostream& operator<< (std::ostream& os, const Point2D& point) {
        os << point.x << " " << point.y;
        return os;
    }

} //namespace vrt

#endif
