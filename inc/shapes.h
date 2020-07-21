#pragma once
#include "rays.h"

namespace RayTracer {

    //hit record
    class HitRecord {
    public:
        void raySide(const Vector&, const Ray&);
        bool inNormal{};
        Point m_point{0,0,0};
        double t{};
        Vector normal{0,0,0};
    };

    // Interface for a hittable object
    class Shape {
    public:
        virtual bool rayHit(const Ray& ray, double t_min, double t_max, HitRecord& log) const = 0;
    };

    class ShapeList : public Shape {
    public:
        ShapeList();
        ShapeList(shared_ptr<Shape>);
        virtual bool rayHit(const Ray&, double, double, HitRecord&) const override;
        void addPointer(shared_ptr<Shape>);
        void removePointer();
        void clearPointers();

    private:
        vector<shared_ptr<Shape>> pointerList;
    };

    class Sphere : public Shape {
    public:
        Sphere(Point,double);
        virtual bool rayHit(const Ray&,double, double,HitRecord&) const override;
        double radius() const;
        Point center() const;

    private:
        Point m_center{0,0,0};
        double m_radius{};
    };

     //function to set ray color
    Color rayColor(const Ray&, const Shape&, int);
} // namespace RayTracer
