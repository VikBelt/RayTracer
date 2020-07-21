#pragma once
// std headerfiles
#include <exception>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <cmath>
#include <limits>

//using directives
using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

namespace RayTracer
{
    //constants
    constexpr double aspect_ratio {16.0/9.0};
    constexpr int image_width {1200};
    constexpr int image_height = static_cast<int>(image_width/aspect_ratio);
    constexpr double pi = 3.14159265;
    constexpr double inf = std::numeric_limits<double>::infinity();
    constexpr int pixelSamples{100};
    constexpr int maxDepth{50};

    //functions
    double degToRad(double degreeAngle);
    double radtoDeg(double radAngle);
    double randomDecimal();
    double randomDecimal(double , double );
    double clipRange(double val, double min, double max);

} //namespace RayTracer
