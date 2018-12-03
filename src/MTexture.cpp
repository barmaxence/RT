#include "MTexture.h"
#include "Utils.h"

#include <algorithm>

// MTexture

MTexture::MTexture(void)
{

}

MTexture::MTexture(const MTexture& src)
{

}

MTexture::MTexture(MTexture&& src)
{

}

MTexture::MTexture(const double s) :
    scale(s)
{

}

MTexture::~MTexture(void)
{

}

MTexture& MTexture::operator=(const MTexture& rhs)
{
    if (this != &rhs)
    {
        scale = rhs.scale;
    }
    return (*this);
}

MTexture& MTexture::operator=(MTexture&& rhs)
{
    if (this != &rhs)
    {
        scale = std::move(rhs.scale);
        rhs.scale = 1.0;
    }
    return (*this);
}

MTextureChecker* MTexture::Checker(const double s)
{
    return new MTextureChecker(s);
}

MTextureWood* MTexture::Wood(const double s)
{
    return new MTextureWood(s);
}

MTextureMarble* MTexture::Marble(const double s)
{
    return new MTextureMarble(s);
}

MTextureCamo* MTexture::Camo(const double s)
{
    return new MTextureCamo(s);
}

MColor MTexture::dColor(const MObject* obj, const MVector& point)
{
    return obj->material.dColor;
}

MColor MTexture::sColor(const MObject* obj, const MVector& point)
{
    return obj->material.sColor;
}

const std::string MTexture::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MTexture {\n\
 %.8lf }", scale);
    return std::string(buf);
}

// MTextureChecker

MTextureChecker::MTextureChecker(void) :
    MTexture()
{

}

MTextureChecker::MTextureChecker(const MTextureChecker& src) :
    MTexture(src)
{

}

MTextureChecker::MTextureChecker(MTextureChecker&& src) :
    MTexture(src)
{

}

MTextureChecker::MTextureChecker(const double s) :
    MTexture(s)
{

}

MTextureChecker::~MTextureChecker(void)
{

}

MTextureChecker& MTextureChecker::operator=(const MTextureChecker& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(rhs);
    }
    return (*this);
}

MTextureChecker& MTextureChecker::operator=(MTextureChecker&& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(std::move(rhs));
    }
    return (*this);
}

MColor MTextureChecker::dColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    p.x = p.x < 0.0 ? -p.x + 1.0 : p.x;
    p.y = p.y < 0.0 ? -p.y + 1.0 : p.y;
    p.z = p.z < 0.0 ? -p.z + 1.0 : p.z;
    if (((int)(p.x) % 2 == 0 && (int)(p.y) % 2 == 0) ||
        ((int)(p.x) % 2 != 0 && (int)(p.y) % 2 != 0))
        ret = MColor::white();
    else
        ret = obj->material.dColor;
    return ret;
}

MColor MTextureChecker::sColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    p.x = p.x < 0.0 ? -p.x + 1.0 : p.x;
    p.y = p.y < 0.0 ? -p.y + 1.0 : p.y;
    p.z = p.z < 0.0 ? -p.z + 1.0 : p.z;
    if (((int)(p.x) % 2 == 0 && (int)(p.y) % 2 == 0) ||
        ((int)(p.x) % 2 != 0 && (int)(p.y) % 2 != 0))
        ret = MColor::white();
    else
        ret = obj->material.sColor;
    return ret;
}

const std::string MTextureChecker::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MTextureChecker {\n\
 %s }", MTexture::toStringDebug().c_str());
    return std::string(buf);
}

// MTextureWood

MTextureWood::MTextureWood(void) :
    MTexture()
{

}

MTextureWood::MTextureWood(const MTextureWood& src) :
    MTexture(src)
{

}

MTextureWood::MTextureWood(MTextureWood&& src) :
    MTexture(src)
{

}

MTextureWood::MTextureWood(const double s) :
    MTexture(s)
{

}

MTextureWood::~MTextureWood(void)
{

}

MTextureWood& MTextureWood::operator=(const MTextureWood& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(rhs);
    }
    return (*this);
}

MTextureWood& MTextureWood::operator=(MTextureWood&& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(std::move(rhs));
    }
    return (*this);
}

MColor MTextureWood::dColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f =  20.0 * _perlin.noise(p.x, p.y, p.z);
    const double w = std::max(0.0, f - (int)f);
    ret = obj->material.dColor * w;
    return ret;
}

MColor MTextureWood::sColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f = 20.0 * _perlin.noise(p.x, p.y, p.z);
    const double w = std::max(0.0, f - (int)f);
    ret = obj->material.sColor * w;
    return ret;
}

const std::string MTextureWood::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MTextureWood {\n\
 %s }", MTexture::toStringDebug().c_str());
    return std::string(buf);
}

// MTextureMarble

MTextureMarble::MTextureMarble(void) :
    MTexture()
{

}

MTextureMarble::MTextureMarble(const MTextureMarble& src) :
    MTexture(src)
{

}

MTextureMarble::MTextureMarble(MTextureMarble&& src) :
    MTexture(src)
{

}

MTextureMarble::MTextureMarble(const double s) :
    MTexture(s)
{

}

MTextureMarble::~MTextureMarble(void)
{

}

MTextureMarble& MTextureMarble::operator=(const MTextureMarble& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(rhs);
    }
    return (*this);
}

MTextureMarble& MTextureMarble::operator=(MTextureMarble&& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(std::move(rhs));
    }
    return (*this);
}

MColor MTextureMarble::dColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f = std::cos(p.x + _perlin.noise(p.x, p.y, p.z));
    ret = obj->material.dColor * f + MColor::white() * (1.0 - f);
    return ret;
}

MColor MTextureMarble::sColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f = std::cos(p.x + _perlin.noise(p.x, p.y, p.z));
    ret = obj->material.sColor * f + MColor::white() * (1.0 - f);
    return ret;
}

const std::string MTextureMarble::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MTextureMarble {\n\
 %s }", MTexture::toStringDebug().c_str());
    return std::string(buf);
}


// MTextureCamo

MTextureCamo::MTextureCamo(void) :
    MTexture()
{

}

MTextureCamo::MTextureCamo(const MTextureCamo& src) :
    MTexture(src)
{

}

MTextureCamo::MTextureCamo(MTextureCamo&& src) :
    MTexture(src)
{

}

MTextureCamo::MTextureCamo(const double s) :
    MTexture(s)
{

}

MTextureCamo::~MTextureCamo(void)
{

}

MTextureCamo& MTextureCamo::operator=(const MTextureCamo& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(rhs);
    }
    return (*this);
}

MTextureCamo& MTextureCamo::operator=(MTextureCamo&& rhs)
{
    if (this != &rhs)
    {
        MTexture::operator=(std::move(rhs));
    }
    return (*this);
}

MColor MTextureCamo::dColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f = _perlin.noise(p.x, p.y, p.z);
    const int i = f * 10.0;
    if (i < 2)
    {
        ret = obj->material.dColor;
    }
    else if (i < 4)
    {
        ret = obj->material.dColor * 0.8;
    }
    else if (i < 6)
    {
        ret = obj->material.dColor * 0.6;
    }
    else if (i < 8)
    {
        ret = obj->material.dColor * 0.4;
    }
    else
    {
        ret = obj->material.dColor * 0.2;
    }
    return ret;
}

MColor MTextureCamo::sColor(const MObject* obj, const MVector& point)
{
    MColor ret;
    MVector p = obj->convert(obj->uv(point)) / scale;
    const double f = _perlin.noise(p.x, p.y, p.z);
    const int i = f * 10.0;
    if (i < 2)
    {
        ret = obj->material.sColor;
    }
    else if (i < 4)
    {
        ret = obj->material.sColor * 0.8;
    }
    else if (i < 6)
    {
        ret = obj->material.sColor * 0.6;
    }
    else if (i < 8)
    {
        ret = obj->material.sColor * 0.4;
    }
    else
    {
        ret = obj->material.sColor * 0.2;
    }
    return ret;
}

const std::string MTextureCamo::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MTextureCamo {\n\
 %s }", MTexture::toStringDebug().c_str());
    return std::string(buf);
}