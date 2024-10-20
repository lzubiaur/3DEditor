#pragma once

#include <memory>
#include <editor/IControl.h>
#include <services/IServiceLocator.h>

namespace Engine
{

class IUIBuilder
{
public:
    using ControlPtr = std::shared_ptr<IControl>;

    virtual ~IUIBuilder() noexcept = default;

    virtual ControlPtr buildMainMenu(IServiceLocator& services) = 0;
    virtual ControlPtr buildNodeGraph(IServiceLocator& services) = 0;
    virtual ControlPtr buildMessageConsole(IServiceLocator& services) = 0;
    
    // Tests
    virtual ControlPtr buildSandboxWindow(IServiceLocator& services) = 0;
};

}