#ifndef VRT_MATERIAL_H
#define VRT_MATERIAL_H

#include "../utility/Ray.h"

//the purpose of the material is to dictate how ays interact with the 
namespace vrt {

    class HitRec;
    
    class Material {
    public:
        //method to produce a scattered ray
        virtual bool scatteredRay (const Ray& in, const HitRec& record, 
            RGBPixel& attenuation, Ray& scattered) const = 0;
    };
}

#endif