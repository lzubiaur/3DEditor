#include <view/ImGui/UIBuilder.h>
#include <view/ImGui/MainMenu.h>
#include <view/ImGui/MessagePanel.h>
#include <view/ImGui/NodeGraph.h>
#include <view/ImGui/MainWindow.h>
#include <view/ImGui/ImGuiDemo.h>
#include <view/ImGui/ImGuiPlotDemo.h>
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
    
ControlPtr UIBuilder::buildControl(ControlType type, IServiceLocator& services)
{
    switch (type)
    {
        // TODO use name and panel or hash
        case ControlType::Panel:
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
    return build<View::MessagePanel>(services);
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

ControlPtr UIBuilder::buildPlotDemoPanel(IServiceLocator& services)
{
    return build<View::ImGuiPlotDemo>(services);
}

}
