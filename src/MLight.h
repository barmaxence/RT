#pragma once

#include "MPositionable.h"

class MLight :
    public MPositionable
{
public:
    MLight(void);
    MLight(const MLight& src);
    MLight(MLight&& src);
    MLight(const MVector& position, const MVector& orientation, const double intensity = 0.0);
    virtual ~MLight(void);
    MLight& operator=(const MLight& rhs);
    MLight& operator=(MLight&& rhs);
    virtual const std::string toStringDebug(void) const;
    double intensity = 1.0;
protected:
private:
};