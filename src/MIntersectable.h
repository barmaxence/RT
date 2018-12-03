#pragma once

#include "MVector.h"
#include "MRay.h"
#include "MSmartPointer.h"

#include <limits>

class MObject;

struct IntersectData
{
    bool hit = false;
    MVector point = MVector::zero();
    double distance = std::numeric_limits<double>::max();
    MRay normal = MVector::zero();
    MObject* obj = nullptr;
};

class MIntersectable
{
public:
    virtual bool intersect(const MRay& ray, IntersectData& data = IntersectData()) = 0;
    virtual MRay normal(const MVector& point) const = 0;
    virtual MVector uv(const MVector& point) const = 0;
protected:
private:
};