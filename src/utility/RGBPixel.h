#ifndef VRT_RGBPIXEL_H
#define VRT_RGBPIXEL_H

#include "helper.h"
#include <iostream>
#include <cmath>

namespace vrt {

    class RGBPixel {
    public:
        RGBPixel();
        RGBPixel(double red, double green, double blue);
        bool operator== (const RGBPixel& other);
        bool operator!= (const RGBPixel& other);
        RGBPixel& operator+=(const RGBPixel& other);
        RGBPixel& operator*=(const RGBPixel& other);
        double r; 
        double g;
        double b;
    };

    //class methods
    RGBPixel::RGBPixel() : r{0},g{0},b{0} {
        //Empty Body
    }

    RGBPixel::RGBPixel(double red, double green, double blue) : r{red}, g{green}, b{blue} {
        //Empty Body
    }

    bool RGBPixel::operator== (const RGBPixel& other){

        if(r != other.r || g != other.g || b != other.b) {
            return false;
        }

        return true;
    }

    bool RGBPixel::operator!= (const RGBPixel& other){
        return !(*this == other);
    }

    RGBPixel& RGBPixel::operator+= (const RGBPixel& other){
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    RGBPixel& RGBPixel::operator*= (const RGBPixel& other){
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    //operator overloading
    inline RGBPixel operator+ (const RGBPixel& pixelOne, const RGBPixel& pixelTwo){
        return RGBPixel(pixelOne.r + pixelTwo.r, pixelOne.g + pixelTwo.g, pixelOne.b + pixelTwo.b);
    }

    inline RGBPixel operator* (const RGBPixel& pixelOne, const RGBPixel& pixelTwo){
        return RGBPixel(pixelOne.r * pixelTwo.r, pixelOne.g * pixelTwo.g, pixelOne.b * pixelTwo.b);
    }

    inline RGBPixel operator* (const RGBPixel& pixel, double a){
        return RGBPixel(a * pixel.r, a * pixel.g, a * pixel.b);
    }

    inline RGBPixel operator* (double a, const RGBPixel& pixel){
        return RGBPixel(a * pixel.r, a * pixel.g, a * pixel.b);
    }

    inline RGBPixel operator/ (const RGBPixel& pixel, double a){
        return RGBPixel(pixel.r / a, pixel.g / a, pixel.b / a);
    }

    inline std::ostream& operator<< (std::ostream& os, const RGBPixel& pixel) {
        double r = pixel.r;
        double g = pixel.g;
        double b = pixel.b;

        // Divide the color by the number of samples.
        double scale = 1.0 / pixelSamples;
        r = std::sqrt(scale*r);
        g = std::sqrt(scale*g);
        b = std::sqrt(scale*b);

        os  << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
            << static_cast<int>(256 * clamp(b, 0.0, 0.999));
        return os;
    }

} //namespace vrt

#endif