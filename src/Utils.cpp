#include "Utils.h"

double MMath::deg2rad(const double deg)
{
    return deg * PI / 180.0;
}

double MMath::rad2deg(const double rad)
{
    return rad * 180.0 / PI;
}

double MMath::clamp(double min, double v, double max)
{
    if (v < min)
        return min;
    if (v > max)
        return max;
    return v;
}

double MMath::random(double min, double max)
{
    return (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * (max - min) + min;
}