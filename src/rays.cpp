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

    //Random Vector 
    Vector Vector::randomVector(){
        return (randomDecimal(),randomDecimal(),randomDecimal());
    }

    Vector Vector::randomVector(double min, double max){
        return (randomDecimal(min,max),randomDecimal(min,max),randomDecimal(min,max));
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
    
    double Vector::magnitude() const{
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

    Vector unitVector(const Vector& source){
       return source/source.magnitude();
    }    

    //Color Utility function
    void writeColor(std::ostream& os, Color pixelColor, int samples) {

        double r = pixelColor.x();
        double g = pixelColor.y();
        double b = pixelColor.z();
        //update color samlpes
        auto scaleFactor = 1.0/samples;
        r =  std::sqrt(r * scaleFactor);
        g = std::sqrt(g * scaleFactor);
        b  = std::sqrt(b * scaleFactor);

        os << static_cast<int>(256 * clipRange(r,0,0.999)) << ' '
            << static_cast<int>(256 * clipRange(g,0,0.999)) << ' '
            << static_cast<int>(256 * clipRange(b,0,0.999   )) << '\n';
    }

    Vector unitSphere(){
        while(true){
            Vector test =  Vector::randomVector(-1,1);
            if(test.magSquared() >= 1) {continue;} 
            return test;
        }
    }

    //method one
    Vector randomUnitVector(){
        double theta = randomDecimal(0,2*pi);
        double len = randomDecimal(-1,1);
        double rad = std::sqrt(1-len*len);
        return Vector(rad*std::cos(theta),rad*std::sin(theta),len);
    }

    //method two
    Vector inHemisphere(const Vector& normal){
        Vector inSphere {unitSphere()};
        if(dot(normal,inSphere) > 0) {
            return inSphere;
        }
        else{
            return -1*inSphere;
        }
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
    
} //namespace RayTracer
