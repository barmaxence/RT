#pragma once

#include <string>

class MWindow
{
public:
    MWindow(void);
    MWindow(const MWindow& src);
    MWindow(MWindow&& src);
    MWindow(const std::size_t w, const std::size_t h);
    virtual ~MWindow(void);
    MWindow& operator=(const MWindow& rhs);
    MWindow& operator=(MWindow&& rhs);
    double getAspectRatio(void) const;
    virtual const std::string toDebugString(void) const;
    std::size_t width = 1024;
    std::size_t height = 576;
protected:
private:
};