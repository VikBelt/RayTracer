#pragma once
// std headerfiles
#include <exception>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <limits>

//using directives
using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

//constants
constexpr double aspect_ratio {16.0/9.0};
constexpr int image_width {1200};
constexpr int image_height = static_cast<int>(image_width/aspect_ratio);
constexpr double pi = 3.14159265;
constexpr double inf = std::numeric_limits<double>::infinity();

//functions
inline double degToRad(double degreeAngle){
    return (pi/180)*degreeAngle;
}
inline double radtoDeg(double radAngle) {
    return (180/pi) * radAngle;
}
