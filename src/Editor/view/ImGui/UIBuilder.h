#pragma once
#include <core/IApplication.h>
#include <editor/IUIBuilder.h>
#include <services/IServiceLocator.h>

namespace Engine
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
