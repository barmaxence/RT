#include "MBox.h"

#include <algorithm>

MBox::MBox(void) :
    MObject()
{
    return;
}

MBox::MBox(const MBox& src) :
    MObject(src)
{
    return;
}

MBox::MBox(MBox&& src) :
    MObject(src)
{
    return;
}

MBox::MBox(const MVector& position, const MVector& orientation, const MVector size) :
    MObject(position, orientation),
    size(size)
{
    return;
}

MBox::~MBox(void)
{
    return;
}

MBox& MBox::operator=(const MBox& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
        size = rhs.size;
    }
    return (*this);
}

MBox& MBox::operator=(MBox&& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
        size = std::move(rhs.size);
        rhs.size = MVector::zero();
    }
    return (*this);
}

bool MBox::intersect(const MRay& ray, IntersectData& data)
{
    MRay r(convert(ray.origin, CoordinateTransform::WORLD2LOCAL), convert(ray.direction, CoordinateTransform::WORLD2LOCAL, MVector::Type::VECTOR));
    const MVector p = MVector::zero();

    MVector bound[2];
    bound[0] = p - size / 2.0;
    bound[1] = p + size / 2.0;
    MVector invR = r.direction;
    invR.x = 1.0 / invR.x;
    invR.y = 1.0 / invR.y;
    invR.z = 1.0 / invR.z;
    int sign[3];
    sign[0] = invR.x < 0.0 ? 1 : 0;
    sign[1] = invR.y < 0.0 ? 1 : 0;
    sign[2] = invR.z < 0.0 ? 1 : 0;

    MVector vMin, vMax;
    vMin.x = (bound[sign[0]].x - r.origin.x) * invR.x;
    vMax.x = (bound[1 - sign[0]].x - r.origin.x) * invR.x;
    vMin.y = (bound[sign[1]].y - r.origin.y) * invR.y;
    vMax.y = (bound[1 - sign[1]].y - r.origin.y) * invR.y;

    if ((vMin.x > vMax.y) || (vMin.y > vMax.x))
    {
        data.hit = false;
        data.distance = 0.0;
        data.point = MVector::zero();
        data.normal = MVector::zero();
        data.obj = nullptr;
        return data.hit;
    }
    if (vMin.y > vMin.x)
    {
        vMin.x = vMin.y;
    }
    if (vMax.y < vMax.x)
    {
        vMax.x = vMax.y;
    }

    vMin.z = (bound[sign[2]].z - r.origin.z) * invR.z;
    vMax.z = (bound[1 - sign[2]].z - r.origin.z) * invR.z;

    if ((vMin.x > vMax.z) || (vMin.z > vMax.x))
    {
        data.hit = false;
        data.distance = 0.0;
        data.point = MVector::zero();
        data.normal = MVector::zero();
        data.obj = nullptr;
        return data.hit;
    }
    if (vMin.z > vMin.x)
    {
        vMin.x = vMin.z;
    }
    if (vMax.z < vMax.x)
    {
        vMax.x = vMax.z;
    }

    data.hit = true;
    data.distance = std::min(vMin.x, vMax.x);
    data.point = ray.origin + (ray.direction * data.distance);
    data.normal = normal(data.point);
    data.obj = this;

    return data.hit;
}

MRay MBox::normal(const MVector& point) const
{
    MVector p = convert(point, CoordinateTransform::WORLD2LOCAL);
    MVector n = MVector::zero();
    p.x /= size.x;
    p.y /= size.y;
    p.z /= size.z;
    double sign;
    if (std::abs(p.x) >= std::abs(p.y) && std::abs(p.x) >= std::abs(p.z))
    {
        sign = p.x < 0.0 ? -1.0 : 1.0;
        n = MVector::unitX();
    }
    if (std::abs(p.y) >= std::abs(p.x) && std::abs(p.y) >= std::abs(p.z))
    {
        sign = p.y < 0.0 ? -1.0 : 1.0;
        n = MVector::unitY();
    }
    if (std::abs(p.z) >= std::abs(p.y) && std::abs(p.z) >= std::abs(p.x))
    {
        sign = p.z < 0.0 ? -1.0 : 1.0;
        n = MVector::unitZ();
    }
    return convert(n * sign, CoordinateTransform::LOCAL2WOLRD, MVector::Type::VECTOR);
}

MVector MBox::uv(const MVector& point) const
{
    return convert(point, CoordinateTransform::WORLD2LOCAL);
}

const std::string MBox::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MBox {\n\
 size : %s\n\
 %s }", size.toStringDebug().c_str(), MObject::toStringDebug().c_str());
    return std::string(buf);
}