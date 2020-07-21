#include "shapes.h"

namespace RayTracer {

    //HitRecord Methods
    void HitRecord::raySide(const Vector& normal, const Ray& incident) {
        if(dot(normal,incident.direction()) > 0){
            inNormal = true; //ray inside shape
        }
        else{
            inNormal = false; //ray outside shape
        }
    }

    //ShapeList Methods
    //constructors
    ShapeList::ShapeList() {/* Empty Body */}
    ShapeList::ShapeList(shared_ptr<Shape> shapePointer) { 
        pointerList.push_back(shapePointer);
    }
    //sizing methods 
    void ShapeList::addPointer(shared_ptr<Shape> shapePointer) {
        pointerList.push_back(shapePointer);
    }

    void ShapeList::removePointer(){
        pointerList.pop_back();
    }

    void ShapeList::clearPointers(){
        pointerList.clear();
    }
    //RayHit method
    bool ShapeList::rayHit(const Ray& ray, double t_min, double t_max, HitRecord& log) const {
        HitRecord tempLog;
        bool shapeHit = false;
        double closestTime = t_max;
        //go through the pointer list
        for (const auto& ref : pointerList) {
            if (ref->rayHit(ray, t_min, closestTime, tempLog)) {
                shapeHit = true;
                closestTime = tempLog.t;
                log = tempLog;
            }
        }

    return shapeHit;

    }

    //Sphere Methods
    //sphere constructor
     Sphere::Sphere(Point center = {0,0,0}, double radius = 0)
        : m_center{center}, m_radius{radius} {}
     //getter functions
     double Sphere::radius() const {
         return m_radius;
     }

     Point Sphere::center() const {
         return m_center;
     }
     //check hit
     bool Sphere::rayHit(const Ray& ray, double t_min, double t_max, HitRecord& log) const {
         Vector OC = ray.origin() - m_center;
         double a = ray.direction().magSquared();
         double half_b = dot(OC,ray.direction());
         double c = OC.magSquared() - (m_radius*m_radius);
         
         double discriminant = (half_b)*(half_b) - a*c;
         //two real roots in quaratic equation - solving for t
         if(discriminant > 0) {
            double zero = (-half_b - std::sqrt(discriminant))/a;
            if(zero > t_min && zero < t_max ){
                log.t = zero;
                log.m_point = ray.position(log.t);
                log.normal = (log.m_point - m_center)/m_radius;
                Vector normal = (log.m_point - m_center) / m_radius;
                log.raySide(normal, ray);
                return true;
             }

            zero = (-half_b + std::sqrt(discriminant))/a;
            if(zero > t_min && zero < t_max) {
                log.t = zero;
                log.m_point - ray.position(log.t);
                log.normal = (log.m_point - m_center)/m_radius;
                Vector normal = (log.m_point - m_center) / m_radius;
                log.raySide(normal, ray);
                return true;
            }
        }
        
        return false; //no real roots so no intersection of ray and sphere
     }

    //function for color gradient
    Color rayColor(const Ray& ray, const Shape& world, int depth) {
        HitRecord log;
        //base case
        if(depth <= 0){
            return Color{0,0,0};
        }
        //recursive case
        if(world.rayHit(ray,0,inf,log)){
            Point target = log.m_point + log.normal + randomUnitVector();
            return 0.5 * rayColor(Ray(log.m_point,target - log.m_point),world,depth-1); 
        }

        Vector unitDirection = unitVector(ray.direction());
        double t = 0.5*(unitDirection.y() + 1.0);
        return (1.0-t)*Color{1.0, 1.0, 1.0} + t*Color{0.5, 0.7, 1.0};
    }

} // namespace RayTracer
