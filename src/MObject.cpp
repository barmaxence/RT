#include "MObject.h"

// MObject

MObject::MObject(void) :
    MPositionable(),
    texture(new MTexture())
{
    return;
}

MObject::MObject(const MObject& src) :
    MPositionable(src),
    material(src.material),
    texture(src.texture)
{
    return;
}

MObject::MObject(MObject&& src) :
    MPositionable(src),
    material(src.material),
    texture(src.texture)
{
    return;
}

MObject::MObject(const MVector& position, const MVector& orientation) :
    MPositionable(position, orientation),
    texture(new MTexture())
{
    return;
}

MObject::~MObject(void)
{
    return;
}

MObject& MObject::operator=(const MObject& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(rhs);
        material = rhs.material;
        texture = rhs.texture;
    }
    return (*this);
}

MObject& MObject::operator=(MObject&& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(std::move(rhs));
        material = std::move(rhs.material);
        rhs.material = MMaterial();
        texture = std::move(rhs.texture);
        rhs.texture = new MTexture();
    }
    return (*this);
}

bool MObject::intersect(const MRay& ray, IntersectData& data)
{
    return false;
}

MRay MObject::normal(const MVector& point) const
{
    return MRay();
}

MVector MObject::uv(const MVector& point) const
{
    return MVector::zero();
}

const std::string MObject::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MObject {\n\
 %s }", MPositionable::toStringDebug().c_str());
    return std::string(buf);
}