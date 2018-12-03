#pragma once

#include "MObject.h"

class MSphere :
    public MObject
{
public:
    MSphere(void);
    MSphere(const MSphere& src);
    MSphere(MSphere&& src);
    MSphere(const MVector& position, const MVector& orientation, double radius = 1.0);
    virtual ~MSphere(void);
    MSphere& operator=(const MSphere& rhs);
    MSphere& operator=(MSphere&& rhs);
    virtual bool intersect(const MRay& ray, IntersectData& data = IntersectData());
    virtual MRay normal(const MVector& point) const;
    virtual MVector uv(const MVector& point) const;
    virtual const std::string toStringDebug(void) const;
    double radius = 1.0;
protected:
private:
};