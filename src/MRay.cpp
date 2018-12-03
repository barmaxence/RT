#include "MRay.h"

MRay::MRay(void)
{
    return;
}

MRay::MRay(const MRay& src) :
    origin(src.origin),
    direction(src.direction)
{
    return;
}

MRay::MRay(MRay&& src) :
    origin(src.origin),
    direction(src.direction)
{
    return;
}

MRay::~MRay(void)
{
    return;
}

MRay::MRay(const MVector& v) :
    origin(MVector::zero()),
    direction(v)
{
    return;
}

MRay::MRay(const MVector& o, const MVector& v) :
    origin(o),
    direction(v)
{
    return;
}

MRay& MRay::operator=(const MRay& rhs)
{
    if (this != &rhs)
    {
        origin = rhs.origin;
        direction = rhs.direction;
    }
    return (*this);
}

MRay& MRay::operator=(MRay&& rhs)
{
    if (this != &rhs)
    {
        origin = std::move(rhs.origin);
        rhs.origin = MVector::zero();
        direction = std::move(rhs.direction);
        rhs.direction = MVector::zero();
    }
    return (*this);
}

const std::string MRay::toString(void) const
{
    char buf[128];
    std::memset(buf, 0, 128);
    sprintf(buf, "{%s , %s}", origin.toString().c_str(), direction.toString().c_str());
    return std::string(buf);
}

const std::string MRay::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MRay {\n\
 origin : %s\n\
 direction : %s }", origin.toStringDebug().c_str(), direction.toStringDebug().c_str());
    return std::string(buf);
}