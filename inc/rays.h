#pragma once
#include <iostream>
#include "helper.h"

using std::sqrt;

namespace RayTracer {
    //class Vector
    class Vector {
        //underlying array
        double array[3] {0,0,0};
    public:
        Vector(double,double,double);
        //operator overloading
        void operator*= (double);
        void operator/=(double);
        void operator+= (const Vector&);
        void operator-();
        double x();
        double y();
        double z();
        static Vector randomVector();
        static Vector randomVector(double,double);
        double magnitude();
        double magnitude() const;
        double magSquared();

        //friend functions
        friend std::ostream& operator<<(std::ostream&, const Vector&);
        friend Vector operator+(const Vector&, const Vector&);
        friend Vector operator-(const Vector&, const Vector&);
        friend Vector operator*(const Vector&, const Vector&);
        friend Vector operator*(const Vector&, const double);
        friend Vector operator*(const double, const Vector&); //commutative
        friend Vector operator/(const Vector&, const double);
        friend double dot(const Vector&, const Vector&);
        friend bool orthagonal(const Vector&, const Vector&);
        friend Vector cross(const Vector&, const Vector&);
        friend Vector unitVector(const Vector&);
    };
    //vector Aliases
    using Point = Vector;
    using Color = Vector;

    //color utility function
    void writeColor(std::ostream&,Color,int);
    Vector unitSphere();
    Vector randomUnitVector(); //render method one
    Vector inHemisphere(const Vector&);
    //Ray Class
    //represents r = r0 + vt - a vector equation
    class Ray {
    public:
        Ray();
        Ray(const Vector&, const Vector&);
        Point origin(); //get origin vector
        Point origin() const;
        Vector direction(); //get direction vector
        Vector direction() const;
        Point position(double t); //get the scale factor
        Point position(double t) const;
    private:
        Point m_origin{0,0,0};
        Vector m_direction{0,0,0};
    };

} //namespace RayTracer
