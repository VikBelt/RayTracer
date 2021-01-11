#ifndef VRT_VECTOR2D_H
#define VRT_VECTOR2D_H

#include <cmath>
#include <iostream>

#include "Vector3D.h"
#include "Point2D.h"

namespace vrt {

    class Vector2D {
    public:
            
        Vector2D();
        Vector2D(double x, double y);
        //the big five
        Vector2D(const Vector2D& source);
        Vector2D& operator=(const Vector2D& source);
        ~Vector2D();
        //operator overloads
        Vector2D& operator+=(const Vector2D& source);
        Vector2D& operator-=(const Vector2D& source);
        Vector2D& operator*=(const Vector2D& source);
        Vector2D& operator/=(const Vector2D& source);
        Vector2D operator-() const;
        double operator[] (int index) const;
        double& operator[] (int index);
        //retrive coordinates 
        double getX();
        double getY();
        double getX() const;
        double getY() const;
        double magnitude();
        double magnitude() const;
        double magSquared();
        double magSquared() const;
        Vector3D toVector3D();
        Vector3D toVector3D() const;
        Point2D toPoint();
    private:
        double* coordinates;
    };

    //class methods
    Vector2D::Vector2D() {
        coordinates = new double [2];
        coordinates[0] = 0;
        coordinates[1] = 0;
    }

    Vector2D::Vector2D(double x, double y) {
        coordinates = new double [2];
        coordinates[0] = x;
        coordinates[1] = y;
    }   

    Vector2D::Vector2D(const Vector2D& source){
        coordinates = new double [2];
        coordinates[0] = source.coordinates[0];
        coordinates[1] = source.coordinates[1];
    }

    Vector2D& Vector2D::operator=(const Vector2D& source){
        coordinates[0] = source.coordinates[0];
        coordinates[1] = source.coordinates[1];
        return *this;
    }

    Vector2D& Vector2D::operator+=(const Vector2D& source){
        coordinates[0] += source.coordinates[0];
        coordinates[1] += source.coordinates[1];
        return *this; 
    }

    Vector2D& Vector2D::operator-=(const Vector2D& source){
        coordinates[0] -= source.coordinates[0];
        coordinates[1] -= source.coordinates[1];
        return *this; 
    }

    Vector2D& Vector2D::operator*=(const Vector2D& source){
        coordinates[0] *= source.coordinates[0];
        coordinates[1] *= source.coordinates[1];
        return *this; 
    }

    Vector2D& Vector2D::operator/=(const Vector2D& source){
        coordinates[0] /= source.coordinates[0];
        coordinates[1] /= source.coordinates[1];
        return *this; 
    }

    Vector2D Vector2D::operator- () const {
        return Vector2D(-coordinates[0],-coordinates[1]);
    }

    Vector2D::~Vector2D(){
        delete [] coordinates;
    }

    double Vector2D::operator[] (int index) const {
        return coordinates[index];
    }

    double& Vector2D::operator[] (int index){
        return coordinates[index];
    }

    double Vector2D::getX(){
        //x-coord. return 
        return coordinates[0];
    }

    double Vector2D::getY(){
        //y-coord. return 
        return coordinates[1];
    }

    double Vector2D::getX() const{
        //x-coord. return 
        return coordinates[0];
    }

    double Vector2D::getY() const{
        //y-coord. return 
        return coordinates[1];
    }

    double Vector2D::magnitude(){
        return std::sqrt(this->magSquared());
    }

    double Vector2D::magnitude() const{
        return std::sqrt(this->magSquared());
    }

    double Vector2D::magSquared(){
        return coordinates[0]*coordinates[0] + coordinates[1]*coordinates[1];
    }

    double Vector2D::magSquared() const {
        return coordinates[0]*coordinates[0] + coordinates[1]*coordinates[1];
    }

    Point2D Vector2D::toPoint(){
        return Point2D(getX(),getY());
    }

    Vector3D Vector2D::toVector3D() {
        return Vector3D(coordinates[0],coordinates[1],0);
    }

    Vector3D Vector2D::toVector3D() const {
        return Vector3D(coordinates[0],coordinates[1],0);
    }

    //utility functions
    inline Vector2D operator+ (const Vector2D& vecOne, const Vector2D& vecTwo){
        double sumX = vecOne.getX() + vecTwo.getX();
        double sumY = vecOne.getY() + vecTwo.getY();
        return Vector2D(sumX, sumY);
    }

    inline Vector2D operator- (const Vector2D& vecOne, const Vector2D& vecTwo){
        double diffX = vecOne.getX() - vecTwo.getX();
        double diffY = vecOne.getY() - vecTwo.getY();
        return Vector2D(diffX, diffY);
    }

    //arithmetic operations
    inline Vector2D operator* (const Vector2D& vector, double t) {
        return Vector2D(t * vector.getX(), t * vector.getY());
    }

    inline Vector2D operator* (double t, const Vector2D& vector) {
        return Vector2D(t * vector.getX(), t * vector.getY());
    }

    inline Vector2D operator/ (const Vector2D& vector, double t) {
        return Vector2D( (1/t) * vector.getX(), (1/t) * vector.getY());
    }

    inline Vector2D operator/ (double t, const Vector2D& vector) {
        return Vector2D( (1/t) * vector.getX(), (1/t) * vector.getY());
    }
    
    //vector operations
    inline double dotProduct(const Vector2D& vecOne, const Vector2D& vecTwo) {
        double result = vecOne.getX() * vecTwo.getX() + vecOne.getY() * vecTwo.getY();
        return result;
    }

    inline Vector2D unitVector(const Vector2D& source){
        return Vector2D(source.getX()/source.magnitude(),source.getY()/source.magnitude());
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector2D& vector) {
        os << vector.getX() << " " << vector.getY();
        return os;
    }

} //namespace vrt

#endif
