#pragma once

#include "MPositionable.h"
#include "MIntersectable.h"
#include "MVector.h"
#include "MMaterial.h"
#include "MTexture.h"

class MTexture;

class MObject :
    public MPositionable,
    public MIntersectable
{
public:
    MObject(void);
    MObject(const MObject& src);
    MObject(MObject&& src);
    MObject(const MVector& position, const MVector& orientation);
    virtual ~MObject(void);
    MObject& operator=(const MObject& rhs);
    MObject& operator=(MObject&& rhs);
    virtual bool intersect(const MRay& ray, IntersectData& data = IntersectData());
    virtual MRay normal(const MVector& point) const;
    virtual MVector uv(const MVector& point) const;
    virtual const std::string toStringDebug(void) const;
    MMaterial material = MMaterial();
    MSmartPointer<MTexture> texture;
protected:
private:
};