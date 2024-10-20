#include <view/ImGui/UIBuilder.h>
#include <view/ImGui/MainMenu.h>
#include <view/ImGui/MessageConsole.h>
#include <view/ImGui/NodeGraph.h>
#include <view/ImGui/MainWindow.h>
#include <core/Injectors.h>

#include <memory>

namespace Forged::View
{
using ControlPtr = UIBuilder::ControlPtr;
using Injector = Forged::Core::Injector;

ControlPtr UIBuilder::buildMainMenu(IServiceLocator& services)
{
    return std::make_shared<MainMenu>(services);
}

ControlPtr UIBuilder::buildNodeGraph(IServiceLocator& services)
{
    return std::make_shared<NodeGraph>();
}

ControlPtr UIBuilder::buildMessageConsole(IServiceLocator& services)
{
    return std::make_shared<MessageConsole>(services);
}

ControlPtr UIBuilder::buildSandboxWindow(IServiceLocator& services)
{
    // TODO use something else than the main window
    return Injector::getUIControlInjector(services).create<std::shared_ptr<MainWindow>>();
}

}
