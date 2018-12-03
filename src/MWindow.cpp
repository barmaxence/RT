#include "MWindow.h"

MWindow::MWindow(void)
{
    return;
}

MWindow::MWindow(const MWindow& src) :
    width(src.width),
    height(src.height)
{
    return;
}

MWindow::MWindow(MWindow&& src) :
    width(src.width),
    height(src.height)
{
    return;
}

MWindow::MWindow(const std::size_t w, const std::size_t h) :
    width(w),
    height(h)
{
    return;
}

MWindow::~MWindow(void)
{
    return;
}

MWindow& MWindow::operator=(const MWindow& rhs)
{
    if (this != &rhs)
    {
        width = rhs.width;
        height = rhs.height;
    }
    return (*this);
}

MWindow& MWindow::operator=(MWindow&& rhs)
{
    if (this != &rhs)
    {
        width = std::move(rhs.width);
        rhs.width = 0;
        height = std::move(rhs.height);
        rhs.height = 0;
    }
    return (*this);
}

double MWindow::getAspectRatio(void) const
{
    return width / height;
}

const std::string MWindow::toDebugString(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MWindow {\n\
 width : %d\n\
 height : %d }", width, height);
    return std::string(buf);
}