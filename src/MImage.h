#pragma once

#include "MVector.h"

#include <string>
#include <vector>
#include <mutex>

class MImage
{
public:
    MImage(void) = delete;
    MImage(const MImage& src);
    MImage(MImage&& src);
    MImage(const std::size_t w, const std::size_t h);
    virtual ~MImage(void);
    MImage& operator=(const MImage& rhs);
    MImage& operator=(MImage&& rhs);
    std::size_t width(void) const;
    std::size_t height(void) const;
    void set(const int x, const int y, const MColor& pixel);
    MColor get(const int x, const int y) const;
    virtual const std::string toStringDebug(void) const;
protected:
    std::size_t _width = 0;
    std::size_t _height = 0;
    std::vector<MColor> _data;
    std::mutex _mutex;
private:
};