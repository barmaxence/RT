#include "MQuaternion.h"

MQuaternion::MQuaternion(void)
{
    return;
}

MQuaternion::MQuaternion(const MQuaternion& src) :
    imaginary(src.imaginary),
    real(src.real)
{
    return;
}

MQuaternion::MQuaternion(MQuaternion&& src) :
    imaginary(src.imaginary),
    real(src.real)
{
    return;
}

MQuaternion::MQuaternion(const MVector& i) :
    imaginary(i)
{
    return;
}

MQuaternion::MQuaternion(const double r, const MVector& i) :
    imaginary(i),
    real(r)
{
    return;
}

MQuaternion::~MQuaternion(void)
{
    return;
}

MQuaternion& MQuaternion::operator=(const MQuaternion& rhs)
{
    if (this != &rhs)
    {
        imaginary = rhs.imaginary;
        real = rhs.real;
    }
    return (*this);
}

MQuaternion& MQuaternion::operator=(MQuaternion&& rhs)
{
    if (this != &rhs)
    {
        imaginary = std::move(rhs.imaginary);
        real = std::move(rhs.real);
        rhs.real = 0.0;
    }
    return (*this);
}

MQuaternion& MQuaternion::operator+=(const MQuaternion& rhs)
{
    imaginary += rhs.imaginary;
    real += rhs.real;
    return (*this);
}

MQuaternion& MQuaternion::operator-=(const MQuaternion& rhs)
{
    imaginary -= rhs.imaginary;
    real -= rhs.real;
    return (*this);
}

MQuaternion& MQuaternion::operator*=(const double rhs)
{
    imaginary *= rhs;
    real *= rhs;
    return (*this);
}

MQuaternion& MQuaternion::operator/=(const double rhs)
{
    imaginary /= rhs;
    real /= rhs;
    return (*this);
}

MQuaternion& MQuaternion::operator*=(const MQuaternion& rhs)
{
    const double r = real * rhs.real - imaginary.dotProduct(rhs.imaginary);
    const MVector i = rhs.imaginary * real + imaginary * rhs.real + imaginary.crossProduct(rhs.imaginary);
    imaginary = i;
    real = r;
    return (*this);
}

MQuaternion MQuaternion::operator+(const MQuaternion& rhs) const
{
    MQuaternion q(*this);
    q += rhs;
    return q;
}

MQuaternion MQuaternion::operator-(const MQuaternion& rhs) const
{
    MQuaternion q(*this);
    q -= rhs;
    return q;
}

MQuaternion MQuaternion::operator*(const double rhs) const
{
    MQuaternion q(*this);
    q *= rhs;
    return q;
}

MQuaternion MQuaternion::operator/(const double rhs) const
{
    MQuaternion q(*this);
    q /= rhs;
    return q;
}

MQuaternion MQuaternion::operator*(const MQuaternion& rhs) const
{
    MQuaternion q(*this);
    q *= rhs;
    return q;
}

bool MQuaternion::operator==(const MQuaternion& rhs) const
{
    return (imaginary == rhs.imaginary && real == rhs.real);
}

bool MQuaternion::operator!=(const MQuaternion& rhs) const
{
    return (imaginary != rhs.imaginary || real != rhs.real);
}

MQuaternion MQuaternion::conjugate(void) const
{
    return MQuaternion(real, imaginary.inverse());
}

MQuaternion MQuaternion::inverse(void) const
{
    return conjugate() * (1.0 / (norm() * norm()));
}

double MQuaternion::norm(void) const
{
    return sqrt(real * real + imaginary.x * imaginary.x + imaginary.y + imaginary.y + imaginary.z * imaginary.z);
}

MVector MQuaternion::toVector(void) const
{
    return imaginary;
}

const std::string MQuaternion::toString(void) const
{
    char buf[128];
    std::memset(buf, 0, 128);
    sprintf(buf, "(%.8lf, %.8lfi, %.8lfj, %.8lfk)", real, imaginary.x, imaginary.y, imaginary.z);
    return std::string(buf);
}

const std::string MQuaternion::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MQuaternion {\n\
 real : %.8lf\n\
 imaginary : %s }", real, imaginary.toStringDebug().c_str());
    return std::string(buf);
}