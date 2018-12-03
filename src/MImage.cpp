#include "MImage.h"

MImage::MImage(const MImage& src) :
    _width(src._width),
    _height(src._height),
    _data(src._data)
{

}

MImage::MImage(MImage&& src) :
    _width(src._width),
    _height(src._height),
    _data(src._data)
{

}

MImage::MImage(const std::size_t w, const std::size_t h) :
    _width(w),
    _height(h),
    _data(std::vector<MColor>(w * h))
{

}

MImage::~MImage(void)
{

}

MImage& MImage::operator=(const MImage& rhs)
{
    if (this != &rhs)
    {
        _width = rhs._width;
        _height = rhs._height;
        _data = rhs._data;
    }
    return (*this);
}

MImage& MImage::operator=(MImage&& rhs)
{
    if (this != &rhs)
    {
        _width = std::move(rhs._width);
        rhs._width = 0;
        _height = std::move(rhs._height);
        rhs._height = 0;
        _data = std::move(rhs._data);
        rhs._data.clear();
    }
    return (*this);
}

std::size_t MImage::width(void) const
{
    return _width;
}

std::size_t MImage::height(void) const
{
    return _height;
}

void MImage::set(const int x, const int y, const MColor& pixel)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _data[_width * y + x] = pixel;
}

MColor MImage::get(const int x, const int y) const
{
    return MColor(_data[_width * y + x]);
}

const std::string MImage::toStringDebug(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MImage {\n\
 width : %d\n\
 height : %d }", _width, _height);
    return std::string(buf);
}