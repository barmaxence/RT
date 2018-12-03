#include "MCamera.h"

// MCamera

MCamera::MCamera(void) :
    MPositionable()
{
    return;
}

MCamera::MCamera(const MCamera& src) :
    MPositionable(src),
    FOVHorizontal(src.FOVHorizontal),
    FOVVertical(src.FOVVertical),
    clippingPlaneNear(src.clippingPlaneNear),
    clippingPlaneFar(src.clippingPlaneFar)
{
    return;
}

MCamera::MCamera(MCamera&& src) :
    MPositionable(src),
    FOVHorizontal(src.FOVHorizontal),
    FOVVertical(src.FOVVertical),
    clippingPlaneNear(src.clippingPlaneNear),
    clippingPlaneFar(src.clippingPlaneFar)
{
    return;
}

MCamera::MCamera(const double FOVH, const double FOVV) :
    MPositionable(),
    FOVHorizontal(FOVH),
    FOVVertical(FOVV)
{
    return;
}

MCamera::MCamera(const MVector& position, const MVector& orientation, const double FOVH, const double FOVV) :
    MPositionable(position, orientation),
    FOVHorizontal(FOVH),
    FOVVertical(FOVV)
{
    return;
}

MCamera::~MCamera(void)
{
    return;
}

MCamera& MCamera::operator=(const MCamera& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(rhs);
        FOVHorizontal = rhs.FOVHorizontal;
        FOVVertical = rhs.FOVVertical;
        clippingPlaneNear = rhs.clippingPlaneNear;
        clippingPlaneFar = rhs.clippingPlaneFar;
    }
    return (*this);
}

MCamera& MCamera::operator=(MCamera&& rhs)
{
    if (this != &rhs)
    {
        MPositionable::operator=(std::move(rhs));
        FOVHorizontal = std::move(rhs.FOVHorizontal);
        rhs.FOVHorizontal = 0.0;
        FOVVertical = std::move(rhs.FOVVertical);
        rhs.FOVVertical = 0.0;
        clippingPlaneNear = std::move(rhs.clippingPlaneNear);
        rhs.clippingPlaneNear = 0.0;
        clippingPlaneFar = std::move(rhs.clippingPlaneFar);
        rhs.clippingPlaneFar = 0.0;
    }
    return (*this);
}

const std::string MCamera::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MCamera {\n\
 FOVHorizontal : %.8lf\n\
 FOVVertical : %.8lf\n\
 clippingPlaneNear : %.8lf\n\
 clippingPlanFar : %.8lf\n\
 %s }", FOVHorizontal, FOVVertical, clippingPlaneNear, clippingPlaneFar, MPositionable::toStringDebug().c_str());
    return std::string(buf);
}