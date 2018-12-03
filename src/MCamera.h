#pragma once

#include "MPositionable.h"

class MCamera :
    public MPositionable
{
public:
    MCamera(void);
    MCamera(const MCamera& src);
    MCamera(MCamera&& src);
    MCamera(const double FOVH, const double FOVV);
    MCamera(const MVector& position, const MVector& orientation, const double FOVH, const double FOVV);
    virtual ~MCamera(void);
    MCamera& operator=(const MCamera& rhs);
    MCamera& operator=(MCamera&& rhs);
    virtual const std::string toStringDebug(void) const override;
    double FOVHorizontal = 45.0;
    double FOVVertical = -1.0;
    double clippingPlaneNear = 0.1;
    double clippingPlaneFar = 1000;
protected:
private:
};