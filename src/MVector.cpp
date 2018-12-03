#include "MVector.h"
#include "Utils.h"

// MVector

std::map<std::string, MVector> MVector::_vectorRegistry;

MVector::MVector(void)
{
    return;
}

MVector::MVector(const MVector& src) : x(src.x), y(src.y), z(src.z)
{
    return;
}

MVector::MVector(MVector&& src) : x(src.x), y(src.y), z(src.z)
{
    return;
}

MVector::MVector(const double v) : x(v), y(v), z(v)
{
    return;
}

MVector::MVector(const double x, const double y, const double z) : x(x), y(y), z(z)
{
    return;
}

MVector::~MVector(void)
{
    return;
}

MVector& MVector::operator=(const MVector& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
    return (*this);
}

MVector& MVector::operator=(MVector&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        rhs.x = 0.0;
        y = std::move(rhs.y);
        rhs.y = 0.0;
        z = std::move(rhs.z);
        rhs.z = 0.0;
    }
    return (*this);
}

MVector& MVector::operator+=(const MVector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return (*this);
}

MVector& MVector::operator-=(const MVector& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return (*this);
}

MVector& MVector::operator*=(const double rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return (*this);
}

MVector& MVector::operator/=(const double rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return (*this);
}

MVector MVector::operator+(const MVector& rhs) const
{
    MVector v(*this);
    v += rhs;
    return v;
}

MVector MVector::operator-(const MVector& rhs) const
{
    MVector v(*this);
    v -= rhs;
    return v;
}

MVector MVector::operator*(const double rhs) const
{
    MVector v(*this);
    v *= rhs;
    return v;
}

MVector MVector::operator/(const double rhs) const
{
    MVector v(*this);
    v /= rhs;
    return v;
}

bool MVector::operator==(const MVector& rhs) const
{
    return (x == rhs.x && y == rhs.y && z == rhs.z);
}

bool MVector::operator!=(const MVector& rhs) const
{
    return (x != rhs.x || y != rhs.y || z != rhs.z);
}

const MVector MVector::zero(void)
{
    return MVector(0.0, 0.0, 0.0);
}

const MVector MVector::unitX(void)
{
    return MVector(1.0, 0.0, 0.0);
}

const MVector MVector::unitY(void)
{
    return MVector(0.0, 1.0, 0.0);
}

const MVector MVector::unitZ(void)
{
    return MVector(0.0, 0.0, 1.0);
}

const MVector MVector::random(void)
{
    return MVector(MMath::random(0.0, 255.0), MMath::random(0.0, 255.0), MMath::random(0.0, 255.0));
}

const MVector MVector::black(void)
{
    return MVector(0.0, 0.0, 0.0);
}

const MVector MVector::white(void)
{
    return MVector(255.0, 255.0, 255.0);
}

const MVector MVector::red(void)
{
    return MVector(255.0, 0.0, 0.0);
}

const MVector MVector::green(void)
{
    return MVector(0.0, 255.0, 0.0);
}

const MVector MVector::blue(void)
{
   return MVector(0.0, 0.0, 255.0);
}

const MVector MVector::grey(void)
{
    return MVector(127.0, 127.0, 127.0);
}

const MVector MVector::yellow(void)
{
    return MVector(255.0, 255.0, 0.0);
}

const MVector MVector::cyan(void)
{
    return MVector(0.0, 255.0, 255.0);
}

const MVector MVector::magenta(void)
{
    return MVector(255.0, 0.0, 255.0);
}

const MVector MVector::get(const std::string& s)
{
    auto it = _vectorRegistry.find(s);
    if (it != std::end(_vectorRegistry))
        return it->second;
    return MVector::zero();
}

void MVector::record(const std::string& s, const MVector& v)
{
    _vectorRegistry.insert(std::make_pair(s, v));
}

MVector MVector::inverse(void) const
{
    return MVector(-x, -y, -z);
}

double MVector::length(void) const
{
    return sqrt(x * x + y * y + z * z);
}

MVector MVector::normalize(void) const
{
    return MVector((*this) / length());
}

double MVector::dotProduct(const MVector& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

MVector MVector::crossProduct(const MVector& rhs) const
{
    MVector v;
    v.x = y * rhs.z - z * rhs.y;
    v.y = z * rhs.x - x * rhs.z;
    v.z = x * rhs.y - y * rhs.x;
    return v;
}

void MVector::clamp(const double min, const double max)
{
    x = MMath::clamp(min, x, max);
    y = MMath::clamp(min, y, max);
    z = MMath::clamp(min, z, max);
}

const std::string MVector::toString(void) const
{
    char buf[128];
    std::memset(buf, 0, 128);
    sprintf(buf, "(%.8lf, %.8lf, %.8lf)", x, y, z);
    return std::string(buf);
}

const std::string MVector::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MVector {\n\
 x : %.8lf\n\
 y : %.8lf\n\
 z : %.8lf }", x, y, z);
    return std::string(buf);
}
