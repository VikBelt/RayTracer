#ifndef VRT_LAMBERTIAN_H
#define VRT_LAMBERTIAN_H

#include "material.h"

// a class for diffuse materials - ir materials that are NOT shiny

namespace vrt {


    class Lambertian : public Material {
    public:
        Lambertian(const RGBPixel& albedo);
        bool scatteredRay (const Ray& in, const HitRec& record, 
            RGBPixel& attenuation, Ray& scattered) const override;
        RGBPixel albedo_;
    };

    //class Methods
    Lambertian::Lambertian(const RGBPixel& albedo) : albedo_{albedo} {
        //Empty Body
    }

    bool Lambertian::scatteredRay(const Ray& in, const HitRec& record, RGBPixel& attenuation, Ray& scattered) const
    {
        Vector3D scatterDirection = record.normal_ + randUnitVector();
        
        //degenerate scatter correction
        if(scatterDirection.nearZero()){
            scatterDirection = record.normal_;
        }

        scattered = Ray(record.point_,scatterDirection);
        attenuation = albedo_;
        return true;
    }
    
} //namespace vrt

#endif