#ifndef VRT_VECTOR3D_H
#define VRT_VECTOR3D_H

#include <cmath>
#include <iostream>
#include "helper.h"
#include "Point3D.h"

namespace vrt {

    class Vector3D {
    public:
            
        Vector3D();
        Vector3D(double x, double y, double z);
        //the big five
        Vector3D(const Vector3D& source);
        Vector3D& operator=(const Vector3D& source);
        ~Vector3D();
        //operator overloads
        Vector3D& operator+=(const Vector3D& source);
        Vector3D& operator-=(const Vector3D& source);
        Vector3D& operator*=(const Vector3D& source);
        Vector3D& operator/=(const Vector3D& source);
        Vector3D operator-() const;
        double operator[] (int index) const;
        double& operator[] (int index);
        //retrive coordinates 
        double getX();
        double getY();
        double getZ();
        double getX() const;
        double getY() const;
        double getZ() const;
        double magnitude();
        double magnitude() const;
        double magSquared();
        double magSquared() const;
        bool nearZero() const;
        Point3D toPoint();
        Point3D toPoint() const;
        //random vector
        static Vector3D randomVector();
        static Vector3D randomVector(double min, double max);
    private:
        double* coordinates;
    };

    //class methods
    Vector3D::Vector3D() {
        coordinates = new double [3];
        coordinates[0] = 0;
        coordinates[1] = 0;
        coordinates[2] = 0;
    }

    Vector3D::Vector3D(double x, double y, double z) {
        coordinates = new double [3];
        coordinates[0] = x;
        coordinates[1] = y;
        coordinates[2] = z;
    }   

    Vector3D::Vector3D(const Vector3D& source){
        coordinates = new double [3];
        coordinates[0] = source.coordinates[0];
        coordinates[1] = source.coordinates[1];
        coordinates[2] = source.coordinates[2];
    }

    Vector3D& Vector3D::operator=(const Vector3D& source){
        coordinates[0] = source.coordinates[0];
        coordinates[1] = source.coordinates[1];
        coordinates[2] = source.coordinates[2];
        return *this;
    }

    Vector3D& Vector3D::operator+=(const Vector3D& source){
        coordinates[0] += source.coordinates[0];
        coordinates[1] += source.coordinates[1];
        coordinates[2] += source.coordinates[2];
        return *this; 
    }

    Vector3D& Vector3D::operator-=(const Vector3D& source){
        coordinates[0] -= source.coordinates[0];
        coordinates[1] -= source.coordinates[1];
        coordinates[2] -= source.coordinates[2];
        return *this; 
    }

    Vector3D& Vector3D::operator*=(const Vector3D& source){
        coordinates[0] *= source.coordinates[0];
        coordinates[1] *= source.coordinates[1];
        coordinates[2] *= source.coordinates[2];
        return *this; 
    }

    Vector3D& Vector3D::operator/=(const Vector3D& source){
        coordinates[0] /= source.coordinates[0];
        coordinates[1] /= source.coordinates[1];
        coordinates[2] /= source.coordinates[2];
        return *this; 
    }

    Vector3D Vector3D::operator- () const {
        return Vector3D(-coordinates[0],-coordinates[1],-coordinates[2]);
    }

    Vector3D::~Vector3D(){
        delete [] coordinates;
    }

    double Vector3D::operator[] (int index) const {
        return coordinates[index];
    }

    double& Vector3D::operator[] (int index){
        return coordinates[index];
    }

    double Vector3D::getX(){
        //x-coord. return 
        return coordinates[0];
    }

    double Vector3D::getY(){
        //y-coord. return 
        return coordinates[1];
    }

    double Vector3D::getZ(){
        //x-coord. return 
        return coordinates[2];
    }

        double Vector3D::getX() const{
        //x-coord. return 
        return coordinates[0];
    }

    double Vector3D::getY() const{
        //y-coord. return 
        return coordinates[1];
    }

    double Vector3D::getZ() const{
        //x-coord. return 
        return coordinates[2];
    }


    double Vector3D::magnitude(){
        return std::sqrt(this->magSquared());
    }

    double Vector3D::magnitude() const{
        return std::sqrt(this->magSquared());
    }

    double Vector3D::magSquared(){
        return coordinates[0]*coordinates[0] + coordinates[1]*coordinates[1] + coordinates[2]*coordinates[2];
    }

    double Vector3D::magSquared() const {
        return coordinates[0]*coordinates[0] + coordinates[1]*coordinates[1] + coordinates[2]*coordinates[2];
    }

    bool Vector3D::nearZero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8; 
        return (fabs(coordinates[0]) < s) && (fabs(coordinates[1]) < s) && (fabs(coordinates[2]) < s);
    }

    Point3D Vector3D::toPoint(){
        return Point3D(getX(),getY(),getZ());
    }

    Point3D Vector3D::toPoint() const {
        return Point3D(getX(),getY(),getZ());
    }

    //static class methods
    Vector3D Vector3D::randomVector(){
        return Vector3D(randomDouble(),randomDouble(),randomDouble());
    }

    Vector3D Vector3D::randomVector(double min, double max) {
        return Vector3D(randomDouble(min,max),randomDouble(min,max),randomDouble(min,max));
    }

    //utility functions
    inline Vector3D operator+ (const Vector3D& vecOne, const Vector3D& vecTwo){
        double sumX = vecOne.getX() + vecTwo.getX();
        double sumY = vecOne.getY() + vecTwo.getY();
        double sumZ = vecOne.getZ() + vecTwo.getZ();
        return Vector3D(sumX, sumY, sumZ);
    }

    inline Vector3D operator- (const Vector3D& vecOne, const Vector3D& vecTwo){
        double diffX = vecOne.getX() - vecTwo.getX();
        double diffY = vecOne.getY() - vecTwo.getY();
        double diffZ = vecOne.getZ() - vecTwo.getZ();
        return Vector3D(diffX, diffY, diffZ);
    }

    //arithmetic operations
    inline Vector3D operator* (const Vector3D& vector, double t) {
        return Vector3D(t * vector.getX(), t * vector.getY(), t * vector.getZ());
    }

    inline Vector3D operator* (double t, const Vector3D& vector) {
        return Vector3D(t * vector.getX(), t * vector.getY(), t * vector.getZ());
    }

    inline Vector3D operator/ (const Vector3D& vector, double t) {
        return Vector3D( (1/t) * vector.getX(), (1/t) * vector.getY(), (1/t) * vector.getZ());
    }

    inline Vector3D operator/ (double t, const Vector3D& vector) {
        return Vector3D( (1/t) * vector.getX(), (1/t) * vector.getY(), (1/t) * vector.getZ());
    }
    
    //vector operations
    inline double dotProduct(const Vector3D& vecOne, const Vector3D& vecTwo) {
        double result = vecOne.getX() * vecTwo.getX() + vecOne.getY() * vecTwo.getY() + vecOne.getZ() * vecTwo.getZ();
        return result;
    }

    inline Vector3D crossProduct(const Vector3D& vecOne, const Vector3D& vecTwo) {
        double resultX = vecOne.getY() * vecTwo.getZ() - vecOne.getZ() * vecTwo.getY();
        double resultY = vecOne.getZ() * vecTwo.getX() - vecOne.getX() * vecTwo.getZ();
        double resultZ = vecOne.getX() * vecTwo.getY() - vecOne.getY() * vecTwo.getX();
        return Vector3D(resultX,resultY,resultZ);
    }

    inline Vector3D unitVector(const Vector3D& source){
        return Vector3D(source.getX()/source.magnitude(),source.getY()/source.magnitude(),source.getZ()/source.magnitude());
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector3D& vector) {
        os << vector.getX() << " " << vector.getY() << " " << vector.getZ();
        return os;
    }

    Vector3D randInUnitSphere() {
        //find a random vector within this range
        while(true) {
            Vector3D vec = Vector3D::randomVector(-1,1);
            if(vec.magSquared() >= 1) {
                continue;
            }
            return vec;
        }
    }

    Vector3D randUnitVector() {
        return unitVector(randInUnitSphere());
    }

    Vector3D vectorReflection(const Vector3D& v, const Vector3D& n){
        Vector3D newVec = v - 2*dotProduct(v,n)*n;
        return newVec;
    }

} //namespace vrt

#endif