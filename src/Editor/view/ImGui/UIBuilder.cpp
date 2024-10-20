#include <editor/view/ImGui/UIBuilder.h>
#include <editor/view/ImGui/MainMenu.h>
#include <editor/view/ImGui/MessageConsole.h>
#include <editor/view/ImGui/NodeGraph.h>
#include <editor/view/ImGui/MainWindow.h>
#include <core/Injectors.h>

#include <memory>

namespace Engine
{
using ControlPtr = UIBuilder::ControlPtr;
using Injector = Engine::Core::Injector;

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
