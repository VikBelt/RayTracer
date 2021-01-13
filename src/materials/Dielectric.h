#ifndef VRT_DIELECTRIC_H
#define VRT_DIELECTRIC_H

#include "../utility/Vector3D.h"
#include "material.h"

namespace vrt {

    //class for a glass-like material
    class Dielectric : public Material {
    public:
        Dielectric(double index);
        bool scatteredRay (const Ray& in, const HitRec& record, 
            RGBPixel& attenuation, Ray& scattered) const override;
    private:
        double index_; //index of refraction of object
        static double reflectance(double cos, double index); //function to use Schlick's appriximation
    };

    //Class Methods
    Dielectric::Dielectric(double index) : index_{index} {
        //Empty Body
    }

    bool Dielectric::scatteredRay(const Ray& in, const HitRec& record, 
        RGBPixel& attenuation, Ray& scattered) const
    {  
        attenuation = RGBPixel(1.0,1.0,1.0);
        //set refraction ration
        double refractionRatio{};
        if(record.frontFace_){
            refractionRatio = 1.0/index_;
        } else {
            refractionRatio = index_;
        }

        Vector3D unitDirection = unitVector(in.getDirectionVector());

        //account for total internal reflection
        double cos = std::fmin(dotProduct(-unitDirection, record.normal_), 1.0);
        double sin = std::sqrt(1.0 - cos*cos);
        bool cannotRefract = refractionRatio * sin > 1.0;
        
        Vector3D direction;
        //decide on if the Ray refracts or reflects
        if (cannotRefract || reflectance(cos, refractionRatio) > randomDouble())
            direction = vectorReflection(unitDirection, record.normal_);
        else
            direction = vectorRefraction(unitDirection, record.normal_, refractionRatio);

        scattered = Ray(record.point_, direction);

        return true;
    }

    double Dielectric::reflectance(double cos, double index) {
        double r0 = (1-index) / (1+index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cos), 5);
    }
}

#endif