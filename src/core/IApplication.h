#pragma once

#include <core/ISystem.h>
#include <core/IPlatform.h>

namespace Engine
{

class IApplication
{
public:
    using SystemPtr = std::shared_ptr<ISystem>;

    virtual void addSystem(SystemPtr system) = 0;
    virtual void removeSystem(SystemPtr system) = 0;

    virtual const IPlatform& getPlatform() const = 0;
    virtual void requestClose() = 0;
};

}