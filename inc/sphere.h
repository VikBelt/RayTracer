#pragma once
#include "rays.h"

namespace RayTracer {

    //hit record
    class HitRecord {
    public:
        Point m_point{0,0,0};
        double t{};
        Vector normal{0,0,0};
    };

    // Abstract class for a hittable object
    class Entity {
    public:
        virtual bool rayHit(const Ray& ray, double t_min, double t_max, HitRecord& log) const = 0;
    };

    class Sphere : public Entity {
    public:
        Sphere(Point,double);
        bool rayHit(const Ray&,double, double,HitRecord&) const override;
        double radius() const;
        Point center() const;
    private:
        Point m_center{0,0,0};
        double m_radius{};
    };

} // namespace RayTracer
