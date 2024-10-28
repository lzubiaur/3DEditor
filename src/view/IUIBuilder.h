#pragma once

#include <memory>
#include <view/IUIControl.h>
#include <services/IServiceLocator.h>

namespace Forged::View
{

class IUIBuilder
{
public:
    using ControlPtr = std::shared_ptr<IUIControl>;

    virtual ~IUIBuilder() noexcept = default;

    virtual ControlPtr buildControl(ControlType type, IServiceLocator& services) = 0;

    virtual ControlPtr buildMainMenu(IServiceLocator& services) = 0;
    virtual ControlPtr buildNodeGraph(IServiceLocator& services) = 0;
    virtual ControlPtr buildMessageConsole(IServiceLocator& services) = 0;
    virtual ControlPtr buildDemoPanel(IServiceLocator& services) = 0;
    
    // Tests
    virtual ControlPtr buildSandboxWindow(IServiceLocator& services) = 0;
};

}