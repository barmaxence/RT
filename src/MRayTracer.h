#pragma once

#include "MScene.h"
#include "MRay.h"
#include "MSmartPointer.h"
#include "MIntersectable.h"
#include "MImage.h"
#include "MPerlinNoise.h"

#define MAX_DEPTH 5
#define BIAS 0.0001
#define THREAD_NUMBER 8

class MRayTracer
{
public:
    enum MSuperSamplingMode
    {
        NONE = 0,
        X4 = 1
    };
    MRayTracer(void) = default;
    MRayTracer(const MRayTracer&) = delete;
    MRayTracer(MRayTracer&&) = delete;
    virtual ~MRayTracer(void) = default;
    MRayTracer& operator=(const MRayTracer&) = delete;
    MRayTracer& operator=(MRayTracer&&) = delete;
    virtual MImage render(void);
    MRay compute(const double x, const double y);
    MColor draw(const MRay& ray, const int depth = 0);
    MColor colorize(const IntersectData& data, const MScene& scene);
    double shadowize(const IntersectData& data, const MSmartPointer<MLight>& light, const MScene& scene);
    double shadowize(const IntersectData& data, const MScene& scene);
    MColor reflect(const IntersectData& data, const MRay ray, const int depth);
    MColor refract(const IntersectData& data, const MRay ray, const int depth);
    double fresnel(const double a, const double b, const double c);
    MScene scene;
    MSuperSamplingMode supersampling = MSuperSamplingMode::NONE;
    MPerlinNoise perlin;
protected:
    void subRender(const std::size_t from, const std::size_t to, MImage& img);
private:
};