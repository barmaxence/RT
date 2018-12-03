#include "MPositionable.h"
#include "MQuaternion.h"

// MPositionable

MPositionable::MPositionable(void)
{
    return;
}

MPositionable::MPositionable(const MPositionable& src) :
    position(src.position),
    orientation(src.orientation)
{
    return;
}

MPositionable::MPositionable(MPositionable&& src) :
    position(src.position),
    orientation(src.orientation)
{
    return;
}

MPositionable::MPositionable(const MVector& position, const MVector& orientation) :
    position(position),
    orientation(orientation)
{
    return;
}

MPositionable::~MPositionable(void)
{
    return;
}

MPositionable& MPositionable::operator=(const MPositionable& rhs)
{
    if (this != &rhs)
    {
        position = rhs.position;
        orientation = rhs.orientation;
    }
    return (*this);
}

MPositionable& MPositionable::operator=(MPositionable&& rhs)
{
    if (this != &rhs)
    {
        position = std::move(rhs.position);
        rhs.position = MVector::zero();
        orientation = std::move(rhs.orientation);
        rhs.orientation = MVector::zero();
    }
    return (*this);
}

MVector MPositionable::convert(const MVector& v, const CoordinateTransform& way, const MVector::Type& t) const
{
    MQuaternion r;
    if (way == CoordinateTransform::WORLD2LOCAL)
    {
        MQuaternion q1(std::cos(MMath::deg2rad(orientation.x) / 2.0), MVector::unitZ() * std::sin(MMath::deg2rad(orientation.x) / 2.0));
        MQuaternion q2(std::cos(MMath::deg2rad(orientation.y) / 2.0), MVector::unitX() * std::sin(MMath::deg2rad(orientation.y) / 2.0));
        MQuaternion q3(std::cos(MMath::deg2rad(orientation.z) / 2.0), MVector::unitY() * std::sin(MMath::deg2rad(orientation.z) / 2.0));
        MQuaternion q(q1 * q2 * q3);
        r = MQuaternion(v);
        if (t == MVector::Type::POINT)
        {
            r -= MQuaternion(position);
        }
        r = q.conjugate() * r * q;
    }
    else
    {
        MQuaternion q1(std::cos(MMath::deg2rad(orientation.x) / 2.0), MVector::unitZ() * std::sin(MMath::deg2rad(orientation.x) / 2.0));
        MQuaternion q2(std::cos(MMath::deg2rad(orientation.y) / 2.0), MVector::unitX() * std::sin(MMath::deg2rad(orientation.y) / 2.0));
        MQuaternion q3(std::cos(MMath::deg2rad(orientation.z) / 2.0), MVector::unitY() * std::sin(MMath::deg2rad(orientation.z) / 2.0));
        MQuaternion q(q1 * q2 * q3);
        r = MQuaternion(v);
        r = q * r * q.conjugate();
        if (t == MVector::Type::POINT)
        {
            r += MQuaternion(position);
        }
    }
    return r.toVector();
}

const std::string MPositionable::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MPostionable {\n\
 position : %s\n\
 orientation : %s }", position.toStringDebug().c_str(), orientation.toStringDebug().c_str());
    return std::string(buf);
}