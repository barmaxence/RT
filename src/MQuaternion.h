#pragma once

#include "MVector.h"

class MQuaternion
{
public:
    MQuaternion(void);
    MQuaternion(const MQuaternion& src);
    MQuaternion(MQuaternion&& src);
    MQuaternion(const MVector& i);
    MQuaternion(const double r, const MVector& i);
    virtual ~MQuaternion(void);
    MQuaternion& operator=(const MQuaternion& rhs);
    MQuaternion& operator=(MQuaternion&& rhs);
    MQuaternion& operator+=(const MQuaternion& rhs);
    MQuaternion& operator-=(const MQuaternion& rhs);
    MQuaternion& operator*=(const double rhs);
    MQuaternion& operator/=(const double rhs);
    MQuaternion& operator*=(const MQuaternion& rhs);
    MQuaternion operator+(const MQuaternion& rhs) const;
    MQuaternion operator-(const MQuaternion& rhs) const;
    MQuaternion operator*(const double rhs) const;
    MQuaternion operator/(const double rhs) const;
    MQuaternion operator*(const MQuaternion& rhs) const;
    bool operator==(const MQuaternion& rhs) const;
    bool operator!=(const MQuaternion& rhs) const;
    MQuaternion conjugate(void) const;
    MQuaternion inverse(void) const;
    double norm(void) const;
    MVector toVector(void) const;
    virtual const std::string toString(void) const;
    virtual const std::string toStringDebug(void) const;
    MVector imaginary = MVector::zero();
    double real = 0.0;
protected:
private:
};