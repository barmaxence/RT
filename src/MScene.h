#pragma once

#include "MWindow.h"
#include "MCamera.h"
#include "MObject.h"
#include "MLight.h"
#include "MSmartPointer.h"

#include <list>
#include <memory>

class MScene
{
public:
    MScene(void);
    MScene(const MScene& src);
    MScene(MScene&& src);
    MScene(const MWindow& window, const MCamera& camera);
    virtual ~MScene(void);
    MScene& operator=(const MScene& rhs);
    MScene& operator=(MScene&& rhs);
    virtual const std::string toDebugString(void) const;
    MWindow window = MWindow();
    MCamera camera = MCamera();
    std::list<MSmartPointer<MObject>> objects;
    std::list<MSmartPointer<MLight>> lights;
    MColor bColor = MColor(55.0, 55.0, 55.0);
protected:
private:
};