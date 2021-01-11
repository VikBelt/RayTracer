#ifndef VRT_HELPER_H
#define VRT_HELPER_H

#include <limits>
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace vrt {

    //contant for pi
    constexpr double PI = 3.1415926535;

    //constant for infinity 
    constexpr double INF = std::numeric_limits<double>::infinity();

    inline double radians(double degrees) {
        return (PI/180) * degrees;
    }

    inline double degrees(double radians) {
        return (180/PI) * radians;
    }

    inline double randomDouble() {
        return std::rand()/(RAND_MAX + 1.0);
    }
    
    inline double randomDouble (double min, double max) {
         return min + (max-min)*randomDouble();
    }

}

#endif