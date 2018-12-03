#include "MPlane.h"

MPlane::MPlane(void) :
    MObject()
{
    return;
}

MPlane::MPlane(const MPlane& src) :
    MObject(src)
{
    return;
}

MPlane::MPlane(MPlane&& src) :
    MObject(src)
{
    return;
}

MPlane::MPlane(const MVector& position, const MVector& orientation) :
    MObject(position, orientation)
{
    return;
}

MPlane::~MPlane(void)
{
    return;
}

MPlane& MPlane::operator=(const MPlane& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
    }
    return (*this);
}

MPlane& MPlane::operator=(MPlane&& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
    }
    return (*this);
}

bool MPlane::intersect(const MRay& ray, IntersectData& data)
{
    //const MRay r(convert(ray.origin, CoordinateTransform::WORLD2LOCAL), convert(ray.direction, CoordinateTransform::WORLD2LOCAL, MVector::Type::VECTOR));
    //const MVector p = MVector::zero();
    //const MVector N = MVector::unitZ();
    //const double t = (p - r.origin).dotProduct(N) / r.direction.dotProduct(N);

    const MVector N = convert(MVector::unitZ(), CoordinateTransform::LOCAL2WOLRD, MVector::Type::VECTOR).normalize();
    const double t = (position - ray.origin).dotProduct(N) / ray.direction.dotProduct(N);

    if (isfinite(t) && t > 0.0001)
    {
        data.hit = true;
        data.distance = t;
        data.point = ray.origin + (ray.direction * data.distance);
        data.normal = normal(data.point);
        data.obj = this;
        return data.hit;
    }
    
    data.hit = false;
    data.distance = 0.0;
    data.point = MVector::zero();
    data.normal = MVector::zero();
    data.obj = nullptr;
    return data.hit;
}

MRay MPlane::normal(const MVector& point) const
{
    MRay ray;
    ray.origin = point;
    const MVector uintZlocal = convert(MVector::unitZ(), CoordinateTransform::LOCAL2WOLRD, MVector::Type::VECTOR);
    ray.direction = uintZlocal.normalize();
    return ray;
}

MVector MPlane::uv(const MVector& point) const
{
    return convert(point, CoordinateTransform::WORLD2LOCAL);
}

const std::string MPlane::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MPlane {\n\
 radius : %.8lf\n\
 %s }", MObject::toStringDebug().c_str());
    return std::string(buf);
}