#pragma once

#include "MVector.h"
#include "Utils.h"

class MPositionable
{
public:
    MPositionable(void);
    MPositionable(const MPositionable& src);
    MPositionable(MPositionable&& src);
    MPositionable(const MVector& position, const MVector& orientation);
    virtual ~MPositionable(void);
    MPositionable& operator=(const MPositionable& rhs);
    MPositionable& operator=(MPositionable&& rhs);
    virtual MVector convert(const MVector& v, const CoordinateTransform& way = CoordinateTransform::LOCAL2WOLRD, const MVector::Type& t = MVector::Type::POINT) const;
    virtual const std::string toStringDebug(void) const;
    /* (x right, y foreward, z top) */
    MVector position = MVector::zero();
    /* (heading, pitch, roll) */
    MVector orientation = MVector::zero();
protected:
private:
};