#pragma once

#include <string>
#include <map>

class MVector
{
public:
    enum Type
    {
        NONE = 0,
        POINT = 1,
        VECTOR = 2,
        COLOR = 3
    };
    MVector(void);
    MVector(const MVector& src);
    MVector(MVector&& src);
    MVector(const double v);
    MVector(const double x, const double y, const double z);
    virtual ~MVector(void);
    MVector& operator=(const MVector& rhs);
    MVector& operator=(MVector&& rhs);
    MVector& operator+=(const MVector& rhs);
    MVector& operator-=(const MVector& rhs);
    MVector& operator*=(const double rhs);
    MVector& operator/=(const double rhs);
    MVector operator+(const MVector& rhs) const;
    MVector operator-(const MVector& rhs) const;
    MVector operator*(const double rhs) const;
    MVector operator/(const double rhs) const;
    bool operator==(const MVector& rhs) const;
    bool operator!=(const MVector& rhs) const;
    static const MVector zero(void);
    static const MVector unitX(void);
    static const MVector unitY(void);
    static const MVector unitZ(void);
    static const MVector random(void);
    static const MVector black(void);
    static const MVector white(void);
    static const MVector red(void);
    static const MVector green(void);
    static const MVector blue(void);
    static const MVector grey(void);
    static const MVector yellow(void);
    static const MVector cyan(void);
    static const MVector magenta(void);
    static const MVector get(const std::string& s);
    static void record(const std::string& s, const MVector& v);
    MVector inverse(void) const;
    double length(void) const;
    MVector normalize(void) const;
    double dotProduct(const MVector& rhs) const;
    MVector crossProduct(const MVector& rhs) const;
    void clamp(const double min, const double max);
    virtual const std::string toString(void) const;
    virtual const std::string toStringDebug(void) const;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
protected:
    static std::map<std::string, MVector> _vectorRegistry;
private:
};

using MColor = MVector;