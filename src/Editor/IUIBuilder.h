#pragma once

#include <memory>
#include <editor/IControl.h>
#include <services/IServiceProvider.h>

namespace Engine
{

class IUIBuilder
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    virtual ~IUIBuilder() noexcept = default;

    virtual ControlPtr buildMainMenu(IServiceProvider& services) = 0;
    virtual ControlPtr buildNodeGraph(IServiceProvider& services) = 0;
};

}