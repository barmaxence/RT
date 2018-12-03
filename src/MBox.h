#pragma once

#include "MObject.h"

class MBox :
    public MObject
{
public:
    MBox(void);
    MBox(const MBox& src);
    MBox(MBox&& src);
    MBox(const MVector& position, const MVector& orientation, const MVector size = MVector(1.0, 1.0, 1.0));
    virtual ~MBox(void);
    MBox& operator=(const MBox& rhs);
    MBox& operator=(MBox&& rhs);
    virtual bool intersect(const MRay& ray, IntersectData& data = IntersectData());
    virtual MRay normal(const MVector& point) const;
    virtual MVector uv(const MVector& point) const;
    virtual const std::string toStringDebug(void) const;
    MVector size = MVector(1.0, 1.0, 1.0);
protected:
private:
};