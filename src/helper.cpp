#include "helper.h"

namespace RayTracer{

    double degToRad(double degreeAngle){
        return (pi/180)*degreeAngle;
    }

    double radtoDeg(double radAngle) {
        return (180/pi) * radAngle;
    }

    double randomDecimal() {
        // Returns a random real in [0,1).
        return rand() / (RAND_MAX + 1.0);
    }

    double randomDecimal(double min, double max) {
        // Returns a random real in [min,max).
        return min + (max-min)*randomDecimal();
    }

    double clipRange(double val, double min, double max){
        if(val > max) {return max;}
        else if(val < min) {return min;}
        else {return val;}
    }
}
