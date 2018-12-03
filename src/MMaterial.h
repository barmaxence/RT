#pragma once

#include "MVector.h"

struct MMaterial
{
    MColor dColor = MColor::black(); // Diffuse  color
    MColor sColor = MColor::black(); // Specular color
    double aK = 0.0; // Ambient  coefficient
    double dK = 0.0; // Diffuse  coefficient
    double sK = 0.0; // Specular coefficient
    double shininess = 0.0; // Shininess constant
    double reflectivity = 0.0;
    double transparency = 0.0;
    double rGlossiness = 0.0;
    double tGlossiness = 0.0;
    double tI = 1.0;
    static MMaterial Random(void);
    static MMaterial Plain(void);
    static MMaterial Glossy(void);
    static MMaterial Metal(void);
    static MMaterial Mirror(void);
    static MMaterial Water(void);
    static MMaterial Plastic(void);
    virtual const std::string toStringDebug(void) const;
};