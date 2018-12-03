#include "Mmaterial.h"
#include "Utils.h"

MMaterial MMaterial::Random(void)
{
    MMaterial m;
    m.dColor = MColor::random();
    m.aK = MMath::random(0.0, 1.0);
    m.dK = MMath::random(0.0, 1.0);
    m.sColor = MColor::random();
    m.sK = MMath::random(0.0, 1.0);
    m.shininess = MMath::random(1.0, 1024.0);
    m.reflectivity = MMath::random(0.0, 1.0);
    m.rGlossiness = 0.0;
    m.transparency = MMath::random(0.0, 1.0);
    m.tGlossiness = 0.0;
    m.tI = MMath::random(0.8, 1.2);
    return m;
}

MMaterial MMaterial::Plain(void)
{
    MMaterial m;
    m.dColor = MColor::random();
    m.aK = 0.1;
    m.dK = 0.4;
    m.sColor = MColor::random();
    m.sK = 0.2;
    m.shininess = 2.0;
    m.reflectivity = 0.0;
    m.rGlossiness = 0.0;
    m.transparency = 0.0;
    m.tGlossiness = 0.0;
    m.tI = 1.0;
    return m;
}

MMaterial MMaterial::Glossy(void)
{
    MMaterial m;
    m.dColor = MColor::random();
    m.aK = 0.1;
    m.dK = 0.8;
    m.sColor = MColor::random();
    m.sK = 0.0;
    m.shininess = 1.0;
    m.reflectivity = 0.0;
    m.rGlossiness = 0.0;
    m.transparency = 0.0;
    m.tGlossiness = 0.0;
    m.tI = 1.0;
    return m;
}

MMaterial MMaterial::Metal(void)
{
    MMaterial m;
    m.dColor = MColor::grey();
    m.aK = 0.1;
    m.dK = 0.4;
    m.sColor = MColor::grey();
    m.sK = 0.4;
    m.shininess = 128.0;
    m.reflectivity = 0.01;
    m.rGlossiness = 0.0;
    m.transparency = 0.0;
    m.tGlossiness = 0.0;
    m.tI = 1.0;
    return m;
}

MMaterial MMaterial::Mirror(void)
{
    MMaterial m;
    m.dColor = MColor::black();
    m.aK = 0.1;
    m.dK = 1.0;
    m.sColor = MColor::black();
    m.sK = 0.5;
    m.shininess = 1.0;
    m.reflectivity = 1.0;
    m.rGlossiness = 0.0;
    m.transparency = 0.0;
    m.tGlossiness = 0.0;
    m.tI = 1.0;
    return m;
}

MMaterial MMaterial::Water(void)
{
    MMaterial m;
    m.dColor = MColor::cyan();
    m.aK = 0.1;
    m.dK = 0.1;
    m.sColor = MColor::cyan();
    m.sK = 0.1;
    m.shininess = 2.0;
    m.reflectivity = 0.0;
    m.rGlossiness = 0.0;
    m.transparency = 0.7;
    m.tGlossiness = 0.0;
    m.tI = 1.33;
    return m;
}

MMaterial MMaterial::Plastic(void)
{
    MMaterial m;
    m.dColor = MColor::white();
    m.aK = 0.1;
    m.dK = 0.1;
    m.sColor = MColor::white();
    m.sK = 0.1;
    m.shininess = 16.0;
    m.reflectivity = 0.0;
    m.rGlossiness = 0.0;
    m.transparency = 0.7;
    m.tGlossiness = 0.0;
    m.tI = 1.0;
    return m;
}

const std::string MMaterial::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MMaterial {\n\
 dColor : %s\n\
 sColor : %s\n\
 aK : %lf\n\
 dK : %lf\n\
 sK : %lf\n\
 shininess : %lf\n\
 reflectivity : %lf\n\
 rGlossiness : %lf\n\
 transparency : %lf\n\
 tGlossiness : %lf\n\
 tI : %lf }", dColor.toStringDebug().c_str(), sColor.toStringDebug().c_str(), aK, dK, sK, shininess, reflectivity, rGlossiness, transparency, tGlossiness, tI);
    return std::string(buf);
}