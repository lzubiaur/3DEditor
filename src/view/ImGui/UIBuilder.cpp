#include <view/ImGui/UIBuilder.h>
#include <view/ImGui/MainMenu.h>
#include <view/ImGui/MessageConsole.h>
#include <view/ImGui/NodeGraph.h>
#include <view/ImGui/MainWindow.h>
#include <view/ImGui/ImGuiDemo.h>
#include <core/Injectors.h>

#include <memory>

namespace Forged::View
{
using ControlPtr = UIBuilder::ControlPtr;
using Injector = Forged::Core::Injector;

template<typename T>
ControlPtr build(IServiceLocator& services)
{
    return Injector::getUIControlInjector(services).create<std::shared_ptr<T>>();
}
    
ControlPtr UIBuilder::buildControl(IUIControl::ControlType type, IServiceLocator& services)
{
    switch (type)
    {
        case IUIControl::ControlType::UIDemoPanel:
            return buildDemoPanel(services);
            break;
        default:
            return nullptr;
    }
}

ControlPtr UIBuilder::buildMainMenu(IServiceLocator& services)
{
    return build<View::MainMenu>(services);
}

ControlPtr UIBuilder::buildNodeGraph(IServiceLocator& services)
{
    return build<View::NodeGraph>(services);
}

ControlPtr UIBuilder::buildMessageConsole(IServiceLocator& services)
{
    return build<View::MessageConsole>(services);
}

ControlPtr UIBuilder::buildSandboxWindow(IServiceLocator& services)
{
    // TODO use something else than the main window
    return build<View::MainWindow>(services);
}

ControlPtr UIBuilder::buildDemoPanel(IServiceLocator& services)
{
    return build<View::ImGuiDemo>(services);
}

}
