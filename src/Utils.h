#pragma once

#include <cstdlib>

#define PI double(3.141592653589793238463)

namespace MMath
{

    double deg2rad(const double deg);

    double rad2deg(const double rad);

    double clamp(double min, double v, double max);

    double random(double min, double max);

}

enum CoordinateTransform
{
    LOCAL2WOLRD = 0,
    WORLD2LOCAL = 1
};