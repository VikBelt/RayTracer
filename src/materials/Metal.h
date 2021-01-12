#ifndef VRT_METAL_H
#define VRT_METAL_H

#include "material.h"

// a class for diffuse materials - ir materials that are NOT shiny

namespace vrt {


    class Metal : public Material {
    public:
        Metal(const RGBPixel& albedo, double fuzz);
        bool scatteredRay (const Ray& in, const HitRec& record, 
            RGBPixel& attenuation, Ray& scattered) const override;
        RGBPixel albedo_;
        double fuzz_;
    };

    //class Methods
    Metal::Metal(const RGBPixel& albedo, double fuzz) {
        //set albedo
        albedo_ = albedo;
        //set fuzz
        if(fuzz < 1) {fuzz_ = fuzz;}
        else {fuzz_ = 1.0;}
    }

    bool Metal::scatteredRay(const Ray& in, const HitRec& record, RGBPixel& attenuation, Ray& scattered) const
    {
        Vector3D refDirection = vectorReflection(unitVector(in.getDirectionVector()),record.normal_);
        scattered = Ray(record.point_, refDirection + fuzz_*randInUnitSphere());
        attenuation = albedo_;
        return (dotProduct(scattered.getDirectionVector(), record.normal_) > 0);
    }
    
} //namespace vrt

#endif