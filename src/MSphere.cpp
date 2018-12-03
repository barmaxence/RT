#include "MSphere.h"

#include <algorithm>

MSphere::MSphere(void) :
    MObject()
{
    return;
}

MSphere::MSphere(const MSphere& src) :
    MObject(src)
{
    return;
}

MSphere::MSphere(MSphere&& src) :
    MObject(src)
{
    return;
}

MSphere::MSphere(const MVector& position, const MVector& orientation, double radius) :
    MObject(position, orientation),
    radius(radius)
{
    return;
}

MSphere::~MSphere(void)
{
    return;
}

MSphere& MSphere::operator=(const MSphere& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
        radius = rhs.radius;
    }
    return (*this);
}

MSphere& MSphere::operator=(MSphere&& rhs)
{
    if (this != &rhs)
    {
        MObject::operator=(rhs);
        radius = rhs.radius;
        rhs.radius = 0.0;
    }
    return (*this);
}

bool MSphere::intersect(const MRay& ray, IntersectData& data)
{
    //const MRay r(convert(ray.origin, CoordinateTransform::WORLD2LOCAL), convert(ray.direction, CoordinateTransform::WORLD2LOCAL, MVector::Type::VECTOR));
    //const MVector p = MVector::zero();
    //const double b = 2.0 * (r.origin - p).dotProduct(r.direction);
    //const double c = (r.origin - p).dotProduct(r.origin - p) - radius * radius;
    //const double d = b * b - 4.0 * c;

    const double b = 2.0 * (ray.origin - position).dotProduct(ray.direction);
    const double c = (ray.origin - position).dotProduct(ray.origin - position) - radius * radius;
    const double d = b * b - 4.0 * c;
    
    if (d < 0.0)
    {
        data.hit = false;
        data.distance = 0.0;
        data.point = MVector::zero();
        data.normal = MVector::zero();
        data.obj = nullptr;
        return data.hit;
    }
    
    const double t1 = (-b - std::sqrt(d)) / 2.0;
    const double t2 = (-b + std::sqrt(d)) / 2.0;

    if (t1 > 0.0001)
    {
        data.hit = true;
        data.distance = t1;
        data.point = ray.origin + (ray.direction * data.distance);
        data.normal = normal(data.point);
        data.obj = this;
        return data.hit;
    }
    
    if (t2 > 0.0001)
    {
    
        data.hit = true;
        data.distance = t2;
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

MRay MSphere::normal(const MVector& point) const
{
    MRay ray;
    ray.origin = point;
    ray.direction = ((point - position) / radius).normalize();
    return ray;
}

MVector MSphere::uv(const MVector& point) const
{
    const MVector p = convert(point, CoordinateTransform::WORLD2LOCAL);
    const MVector r = MVector((0.5 + std::atan2(p.x, p.y) / (2.0 * PI)) * 2.0 - 1.0, (0.5 - std::asin(p.z / radius) / (2.0 * PI)) * 2.0 - 1.0, 1.0) * radius;
    return r;
}

const std::string MSphere::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MSphere {\n\
 radius : %.8lf\n\
 %s }", radius, MObject::toStringDebug().c_str());
    return std::string(buf);
}