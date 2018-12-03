#include "MRayTracer.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <memory>

MImage MRayTracer::render(void)
{
    auto a = std::chrono::steady_clock::now();
    auto& w = scene.window;
    MImage img(w.width, w.height);
    std::vector<std::unique_ptr<std::thread>> thd;
    thd.reserve(THREAD_NUMBER);
    const std::size_t n = img.height() / THREAD_NUMBER;
    for (auto i = 0; i < THREAD_NUMBER; ++i)
    {
        thd.emplace_back(std::make_unique<std::thread>(&MRayTracer::subRender, this, n * i, n * (i + 1), std::ref(img)));
    }
    for (auto i = 0; i < THREAD_NUMBER; ++i)
    {
        thd[i]->join();
    }
    auto b = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() << std::endl;
    return std::move(img);
}

MRay MRayTracer::compute(const double x, const double y)
{
    const auto w = scene.window;
    const auto c = scene.camera;
    const auto ratio = w.getAspectRatio();
    const auto near = c.clippingPlaneNear;
    const auto far = c.clippingPlaneFar;

    const double norm_x = (x / (double(w.width - 1.0) * 0.5) - 1.0) / ratio;
    const double norm_y = 1.0 - y / (double(w.height - 1.0) * 0.5);

    const double frustrum_x = std::tan(MMath::deg2rad(c.FOVHorizontal) * 0.5) * norm_x;
    const double frustrum_y = std::tan(MMath::deg2rad(c.FOVVertical) * 0.5) * norm_y;

    const MVector P1(frustrum_x * near, near, frustrum_y * near);
    const MVector P2(frustrum_x * far, far, frustrum_y * far);
    const MVector P = P2 - P1;

    const MVector A1 = c.convert(P1);
    const MVector A2 = c.convert(P2);

    return MRay(A1, (A2 - A1).normalize());
}

MColor MRayTracer::draw(const MRay& ray, const int depth)
{
    MColor pColor = MColor::black();

    IntersectData data;
    for (auto& obj : scene.objects)
    {
        IntersectData hitData;
        if (obj->intersect(ray, hitData))
        {
            if (hitData.distance < data.distance)
            {
                data = hitData;
            }
        }
    }

    if (data.hit && data.obj)
    {
        pColor = colorize(data, scene);
        
        //shadow
        //const double sFactor = shadowize(data, scene);
        //pColor *= sFactor;

        if (depth < MAX_DEPTH)
        {
            // reflection
            if (data.obj->material.reflectivity > 0.0)
            {
                const MColor rColor = reflect(data, ray, depth)/* * data.obj->material.reflectivity*/;
                pColor += rColor;
            }
        
            // transparency
            if (data.obj->material.transparency > 0.0)
            {
                const MColor tColor = refract(data, ray, depth)/* * data.obj->material.transparency*/;
                pColor += tColor;
            }
        }
    }
    else
    {
        if (depth < 1)
        {
            pColor = scene.bColor;
        }
        else
        {
            pColor = MColor::black();
        }
    }
    
    pColor.clamp(0.0, 255.0);

    return pColor;
}

MColor MRayTracer::colorize(const IntersectData& data, const MScene& scene)
{
    MVector ambient, diffuse, specular;

    // ambient
    const MColor aColor = data.obj->material.dColor;
    ambient = aColor * data.obj->material.aK;

    for (auto& light : scene.lights)
    {
        // shadow
        const double sFactor = shadowize(data, light, scene);
        //const double sFactor = 1.0;

        // diffuse
        MVector L = light->position - data.point;
        const double dL = L.length();
        L = L.normalize();
        const MVector N = data.normal.direction;
        const double attenuate = 1.0/* / std::pow(dL, 1.0 / 50.0)*/;
        const double NdL = N.dotProduct(L);
        const double dIntensity = std::max(0.0, NdL);
        const MColor dColor = data.obj->texture->dColor(data.obj, data.point);
        diffuse += dColor * light->intensity * dIntensity * attenuate * data.obj->material.dK * sFactor;

        // specular
        MVector V = scene.camera.position - data.point;
        V = V.normalize();
        MVector R = (N * 2.0 * L.dotProduct(N)) - L;
        R = R.normalize();
        const double RdV = R.dotProduct(V);
        const double sIntensity = std::pow(std::max(0.0, RdV), data.obj->material.shininess);
        const MColor sColor = data.obj->texture->sColor(data.obj, data.point);
        specular += sColor * light->intensity * sIntensity * attenuate * data.obj->material.sK * sFactor;
    }

    return ambient + diffuse + specular;
}

double MRayTracer::shadowize(const IntersectData& data, const MSmartPointer<MLight>& light, const MScene& scene)
{
    const MVector sDir = (light->position - data.point).normalize();
    const MRay sRay(data.point, sDir);
    bool shadow = false;
    for (auto& obj : scene.objects)
    {
        IntersectData hitData;
        if (obj.get() != data.obj && obj->intersect(sRay, hitData) && hitData.distance < (light->position - data.point).length())
        {
            shadow = true;
            break;
        }
    }
    return (shadow ? 0.0 : 1.0);
}

double MRayTracer::shadowize(const IntersectData& data, const MScene& scene)
{
    const double shado_min = 0.45;
    int shadowed_by_n_lights = 0;
    for (auto& light : scene.lights)
    {
        const MVector sDir = (light->position - data.point).normalize();
        const MRay sRay(data.point, sDir);
    
        bool shadow = false;
        for (auto& obj : scene.objects)
        {
            IntersectData hitData;
            if (obj.get() != data.obj && obj->intersect(sRay, hitData) && hitData.distance < (light->position - data.point).length())
            {
                ++shadowed_by_n_lights;
                break;
            }
        }
    }
    const double illuminated_by_lights = scene.lights.size() - shadowed_by_n_lights;
    const double ratio = illuminated_by_lights / scene.lights.size();
    return ((shadowed_by_n_lights >0) ? ratio : 1.0);
}

MColor MRayTracer::reflect(const IntersectData& data, const MRay ray, const int depth)
{
    const MVector V = ray.direction;
    const MVector N = data.normal.direction;
    MVector R = V - N * 2.0 * V.dotProduct(N);
    R = R + MVector::random() * data.obj->material.rGlossiness;
    R = R.normalize();
    const MRay rRay(data.point + N * BIAS, R);
    const MColor rColor = draw(rRay, depth + 1) * data.obj->material.reflectivity;
    return rColor;
}

MColor MRayTracer::refract(const IntersectData& data, const MRay ray, const int depth)
{
    //MRay tRayA = ray;
    //tRayA.origin = data.point;
    //const MColor tColor = draw(tRayA, depth + 1);
    //return tColor * data.obj->material.transparency;

    double n = 1.0 / data.obj->material.tI;
    MVector N = data.normal.direction;
    const MVector V = ray.direction;
    //const double coeff = fresnel(std::pow(1.0 - (-V.dotProduct(N)), 3.0), 1.0, 0.1);

    if (MMath::clamp(-1.0, V.dotProduct(N), 1.0) > 0.0)
    {
        n = data.obj->material.tI / 1.0;
        N = N.inverse();
    }
    
    const MVector R = (N.crossProduct((N.inverse()).crossProduct(V)) * n) - (N * std::sqrt(1.0 - std::pow(n, 2.0) * (N.crossProduct(V)).dotProduct(N.crossProduct(V))));
    const MRay tRay(data.point - N * BIAS, R.normalize());
    const MColor tColor = draw(tRay, depth + 1) * data.obj->material.transparency;
    //const MColor rColor = reflect(data, ray, depth + 1);
    //return rColor * coeff + tColor * (1.0 - coeff);
    return tColor;
}

double MRayTracer::fresnel(const double a, const double b, const double c)
{
    return b * c + a * (1.0 - c);
}

void MRayTracer::subRender(const std::size_t from, const std::size_t to, MImage& img)
{
    for (auto y = from; y < to; ++y)
    {
        for (auto x = 0; x < img.width(); ++x)
        {
            MColor pixelColor;
            if (supersampling == MSuperSamplingMode::NONE)
            {
                const MRay ray = compute(x, y);
                pixelColor = draw(ray);
            }
            if (supersampling == MSuperSamplingMode::X4)
            {
                for (double i = x; i < x + 1.0; i += 0.5)
                {
                    for (double j = y; j < y + 1.0; j += 0.5)
                    {
                        const MRay ray = compute(i, j);
                        pixelColor += (draw(ray) * 0.25);
                    }
                }
            }
            img.set((int)x, (int)y, pixelColor);
        }
    }
}