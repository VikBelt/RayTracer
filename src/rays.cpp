#include "rays.h"

namespace RayTracer {
    /* Vector Class Methods 
    //Vector Constructor
    */

    Vector::Vector(double x_in = 0, double y_in = 0, double z_in = 0) {
        array[0] = x_in;
        array[1] = y_in;
        array[2] = z_in;
    }
    //Vector operator overloading
    void Vector::operator-(){
        array[0] = -array[0];
        array[1] = -array[1];
        array[2] = -array[2];
    }

    void Vector::operator*= (double scale){
        array[0] *= scale;
        array[1] *= scale;
        array[2] *= scale;
    }

    void Vector::operator/= (double scale){
        array[0] *= (1/scale);
        array[1] *= (1/scale);
        array[2] *= (1/scale);
    }

    void Vector::operator+= (const Vector& source){
        array[0] += source.array[0];
        array[1] += source.array[1];
        array[2] += source.array[2];
    }
    // Vector getter functions
    double Vector::x() {
        return array[0];
    }

    double Vector::y(){
        return array[1];
    }

    double Vector::z(){
        return array[2];
    }
 
    //function to return vector magnitude & squared magnitude
    double Vector::magnitude(){
        return std::sqrt((array[0]*array[0]) + (array[1]*array[1]) + (array[2]*array[2]));
    }

    double Vector::magSquared(){
        return ((array[0]*array[0]) + (array[1]*array[1]) + (array[2]*array[2]));
    }

    //dot (scalar) product
    double dot(const Vector& vecOne, const Vector& vecTwo){
        return vecOne.array[0]*vecTwo.array[0]+vecOne.array[1]*vecTwo.array[1]+vecOne.array[2]*vecTwo.array[2];
    }

    //cross  (vector) product
    Vector cross(const Vector& vecOne, const Vector& vecTwo) {
        Vector result{0,0,0};
        //define cross
        result.array[0] = (vecOne.array[1] * vecTwo.array[2]) - (vecOne.array[2] * vecTwo.array[1]);
        result.array[1] = (vecOne.array[2] * vecTwo.array[0]) - (vecOne.array[0] * vecTwo.array[2]);
        result.array[2] = (vecOne.array[0] * vecTwo.array[1]) - (vecOne.array[1] * vecTwo.array[0]);
        return result;

    }

    //more operator overloading
    std::ostream& operator<< (std::ostream& out, const Vector& source) {
        return out<<source.array[0]<<" "<<source.array[1]<<" "<<source.array[2]; //output to console
    }

    Vector operator+ (const Vector& vecOne, const Vector& vecTwo){
        Vector result{0,0,0};
        result.array[0] = vecOne.array[0] + vecTwo.array[0];
        result.array[1] = vecOne.array[1] + vecTwo.array[1];
        result.array[2] = vecOne.array[2] + vecTwo.array[2];
        return result;
    }

    Vector operator- (const Vector& vecOne, const Vector& vecTwo){
        Vector result{0,0,0};
        result.array[0] = vecOne.array[0] - vecTwo.array[0];
        result.array[1] = vecOne.array[1] - vecTwo.array[1];
        result.array[2] = vecOne.array[2] - vecTwo.array[2];
        return result;
    }

    Vector operator* (const Vector& vecOne, const Vector& vecTwo){
        Vector result{0,0,0};
        result.array[0] = vecOne.array[0] * vecTwo.array[0];
        result.array[1] = vecOne.array[1] * vecTwo.array[1];
        result.array[2] = vecOne.array[2] * vecTwo.array[2];
        return result;
    }

    Vector operator* (const Vector& source, double scaleFactor){
        Vector result{0,0,0};
        result.array[0] = source.array[0]*scaleFactor;
        result.array[1] = source.array[1]*scaleFactor;
        result.array[2] = source.array[2]*scaleFactor;
        return result;
    }

    Vector operator* (double scaleFactor,const Vector& source) {
        return source*scaleFactor;
    }

    Vector operator/ (const Vector& source, double scaleFactor){
        Vector result{0,0,0};
        result.array[0] = source.array[0]*(1/scaleFactor);
        result.array[1] = source.array[1]*(1/scaleFactor);
        result.array[2] = source.array[2]*(1/scaleFactor);
        return result;
    }

    bool orthagonal(const Vector& vectorOne, const Vector& vectorTwo){
        if(dot(vectorOne, vectorTwo) == 0){
            return true;
        }
        else{
            return false;
        }
    }

    Vector unitVector(Vector& source){
       return source/source.magnitude();
    }    

    //Color Utility function
    void writeColor(std::ostream& out, Color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
    }

    /*
    //Ray Class Methods
    //Constructors */

    Ray::Ray() {/*Empty Body*/}

    Ray::Ray(const Vector& orig, const Vector& direc) : m_origin{orig}, m_direction{direc} {
        //Empty Body Constructor
    }
    //get the origin
    Point Ray::origin() {
        return m_origin;
    }

    Point Ray::origin() const {
        return m_origin;
    }
    //get the direction vector
    Vector Ray::direction() { 
        return m_direction;
    }

    Vector Ray::direction() const {
        return m_direction;
    }

    Point Ray::position(double t){
        return m_origin + m_direction*t;
    }

    Point Ray::position(double t) const {
        return m_origin + m_direction*t;
    }
    
    //function for color gradient
    Color rayColor(Ray& scene) {
        //check hitSphere discriminant
        double t = hitSphere(Point{0,0,-1},0.5,scene);
        if(t > 0){
            Vector temp = scene.position(t);
            temp = temp - Vector{0,0,-1};
            Vector N = unitVector(temp);
            return 0.5* Color{N.x()+1, N.y()+1, N.z()+1};
        }

        Vector scene_direction = scene.direction();
        Vector unit_direction = unitVector(scene_direction);
        t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
    }

    //hit Sphere - here is essentially a quadratic eqauation
    double hitSphere(const Point& C, double radius, const Ray& ray) {
        Point A = ray.m_origin;
        Vector B = ray.m_direction;
        // want at^2 + bt+ c
        double a = dot(B,B);
        double half_b = dot(B,A-C);
        double c = dot(A-C,A-C) - (radius*radius);
        //do discriminant check
        double discriminant = half_b*half_b - a*c;
        if(discriminant < 0) { return -1.0; }
        else { return (-half_b - std::sqrt(discriminant))/a; }
    }

} //namespace RayTracer
