#include "MScene.h"

MScene::MScene(void)
{
    return;
}

MScene::MScene(const MScene& src) :
    window(src.window),
    camera(src.camera)
{
    return;
}

MScene::MScene(MScene&& src) :
    window(src.window),
    camera(src.camera)
{
    return;
}

MScene::MScene(const MWindow& window, const MCamera& camera) :
    window(window),
    camera(camera)
{
    return;
}

MScene::~MScene(void)
{
    return;
}

MScene& MScene::operator=(const MScene& rhs)
{
    if (this != &rhs)
    {
        window = rhs.window;
        camera = rhs.camera;
    }
    return (*this);
}

MScene& MScene::operator=(MScene&& rhs)
{
    if (this != &rhs)
    {
        window = std::move(rhs.window);
        camera = std::move(rhs.camera);
    }
    return (*this);
}

const std::string MScene::toDebugString(void) const
{
    char buf[2048];
    std::memset(buf, 0, 2048);
    sprintf(buf, "\
MScene {\n\
 window : %s\n\
 camera : %s }", window.toDebugString().c_str(), camera.toStringDebug().c_str());
    return std::string(buf);
}