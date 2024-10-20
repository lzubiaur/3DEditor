#pragma once
#include <core/IApplication.h>
#include <view/IUIBuilder.h>
#include <services/IServiceLocator.h>

namespace Forged::View
{

class UIBuilder : public IUIBuilder
{
public:
    UIBuilder::UIBuilder() = default;

    ControlPtr buildMainMenu(IServiceLocator& services) override;
    ControlPtr buildNodeGraph(IServiceLocator& services) override;
    ControlPtr buildMessageConsole(IServiceLocator& services) override;
    ControlPtr buildSandboxWindow(IServiceLocator& services) override;
};

}
