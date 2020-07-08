#pragma once
#include <iostream>
#include <cmath>

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
        double magnitude();

        //utility functions
        friend std::ostream& operator<<(std::ostream&, const Vector&);
        friend Vector operator+(const Vector&, const Vector&);
        friend Vector operator-(const Vector&, const Vector&);
        friend Vector operator*(const Vector&, const Vector&);
        friend Vector operator*(const Vector&, const double);
        friend Vector operator*(const double, const Vector&); //commutative
        friend Vector operator/(const Vector&, const double);
        friend double dot(const Vector&, const Vector&);
        friend Vector cross(const Vector&, const Vector&);
        friend Vector unitVector(Vector&);
    };
    //vector Aliases
    using Point = Vector;
    using Color = Vector;

    //color utility function
    void writeColor(std::ostream&,Color);

    //Ray Class
    //represents r = r0 + vt - a vector equation
    class Ray {
    public:
        Ray();
        Ray(const Vector&, const Vector&);
        Point origin(); //get origin vector
        Vector direction(); //get direction vector
        Point position(double t); //get the scale factor
        friend double hitSphere(const Point&,double,const Ray&);
    private:
        Point m_origin{0,0,0};
        Vector m_direction{0,0,0};
    };

    //function to set ray color
    Color rayColor(Ray&);
} //namespace RayTracer
