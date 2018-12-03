#pragma once

#include "MObject.h"

class MPlane :
    public MObject
{
public:
    MPlane(void);
    MPlane(const MPlane& src);
    MPlane(MPlane&& src);
    MPlane(const MVector& position, const MVector& orientation);
    virtual ~MPlane(void);
    MPlane& operator=(const MPlane& rhs);
    MPlane& operator=(MPlane&& rhs);
    virtual bool intersect(const MRay& ray, IntersectData& data = IntersectData());
    virtual MRay normal(const MVector& point) const;
    virtual MVector uv(const MVector& point) const;
    virtual const std::string toStringDebug(void) const;
protected:
private:
};
