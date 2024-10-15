#pragma once

#include <core/IPlatform.h>

namespace Engine
{

class IApplication
{
public:
    virtual const IPlatform& getPlatform() const = 0;
    virtual void requestClose() = 0;
};

}