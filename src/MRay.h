#pragma once

#include "MVector.h"

class MRay
{
public:
    MRay(void);
    MRay(const MRay& src);
    MRay(MRay&& src);
    MRay(const MVector& v);
    MRay(const MVector& o, const MVector& v);
    virtual ~MRay(void);
    MRay& operator=(const MRay& rhs);
    MRay& operator=(MRay&& rhs);
    virtual const std::string toString(void) const;
    virtual const std::string toStringDebug(void) const;
    MVector origin = MVector::zero();
    MVector direction = MVector::zero();
protected:
private:
};