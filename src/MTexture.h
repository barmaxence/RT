#pragma once

#include "MObject.h"
#include "MPerlinNoise.h"

class MTextureChecker;
class MTextureWood;
class MTextureMarble;
class MTextureCamo;

class MTexture
{
public:
    MTexture(void);
    MTexture(const MTexture& src);
    MTexture(MTexture&& src);
    MTexture(const double s);
    ~MTexture(void);
    MTexture& operator=(const MTexture& rhs);
    MTexture& operator=(MTexture&& rhs);
    static MTextureChecker* Checker(const double s = 1.0);
    static MTextureWood* Wood(const double s = 1.0);
    static MTextureMarble* Marble(const double s = 1.0);
    static MTextureCamo* Camo(const double s = 1.0);
    virtual MColor dColor(const MObject* obj, const MVector& point);
    virtual MColor sColor(const MObject* obj, const MVector& point);
    virtual const std::string toStringDebug(void) const;
    double scale = 1.0;
protected:
private:
};

class MTextureChecker :
    public MTexture
{
public:
    MTextureChecker(void);
    MTextureChecker(const MTextureChecker& src);
    MTextureChecker(MTextureChecker&& src);
    MTextureChecker(const double s);
    ~MTextureChecker(void);
    MTextureChecker& operator=(const MTextureChecker& rhs);
    MTextureChecker& operator=(MTextureChecker&& rhs);
    virtual MColor dColor(const MObject* obj, const MVector& point);
    virtual MColor sColor(const MObject* obj, const MVector& point);
    virtual const std::string toStringDebug(void) const;
protected:
private:
};

class MTextureWood :
    public MTexture
{
public:
    MTextureWood(void);
    MTextureWood(const MTextureWood& src);
    MTextureWood(MTextureWood&& src);
    MTextureWood(const double s);
    ~MTextureWood(void);
    MTextureWood& operator=(const MTextureWood& rhs);
    MTextureWood& operator=(MTextureWood&& rhs);
    virtual MColor dColor(const MObject* obj, const MVector& point);
    virtual MColor sColor(const MObject* obj, const MVector& point);
    virtual const std::string toStringDebug(void) const;
protected:
    MPerlinNoise _perlin;
private:
};

class MTextureMarble :
    public MTexture
{
public:
    MTextureMarble(void);
    MTextureMarble(const MTextureMarble& src);
    MTextureMarble(MTextureMarble&& src);
    MTextureMarble(const double s);
    ~MTextureMarble(void);
    MTextureMarble& operator=(const MTextureMarble& rhs);
    MTextureMarble& operator=(MTextureMarble&& rhs);
    virtual MColor dColor(const MObject* obj, const MVector& point);
    virtual MColor sColor(const MObject* obj, const MVector& point);
    virtual const std::string toStringDebug(void) const;
protected:
    MPerlinNoise _perlin;
private:
};

class MTextureCamo :
    public MTexture
{
public:
    MTextureCamo(void);
    MTextureCamo(const MTextureCamo& src);
    MTextureCamo(MTextureCamo&& src);
    MTextureCamo(const double s);
    ~MTextureCamo(void);
    MTextureCamo& operator=(const MTextureCamo& rhs);
    MTextureCamo& operator=(MTextureCamo&& rhs);
    virtual MColor dColor(const MObject* obj, const MVector& point);
    virtual MColor sColor(const MObject* obj, const MVector& point);
    virtual const std::string toStringDebug(void) const;
protected:
    MPerlinNoise _perlin;
private:
};