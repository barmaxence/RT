#include "MLight.h"

MLight::MLight(void) :
    MPositionable()
{
    return;
}

MLight::MLight(const MLight& src) :
    MPositionable(src)
{
    return;
}

MLight::MLight(MLight&& src) :
    MPositionable(src)
{
    return;

}

MLight::MLight(const MVector& position, const MVector& orientation, const double intensity) :
    MPositionable(position, orientation),
    intensity(intensity)
{
    return;
}

MLight::~MLight(void)
{
    return;
}

MLight& MLight::operator=(const MLight& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(rhs);
        intensity = rhs.intensity;
    }
    return (*this);
}

MLight& MLight::operator=(MLight&& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(rhs);
        intensity = rhs.intensity;
        rhs.intensity = 0.0;
    }
    return (*this);
}

const std::string MLight::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MLight {\n\
 %s }", MPositionable::toStringDebug().c_str());
    return std::string(buf);
}