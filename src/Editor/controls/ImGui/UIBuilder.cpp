#include <editor/controls/ImGui/UIBuilder.h>
#include <editor/controls/ImGui/MainMenu.h>
#include <editor/controls/ImGui/MessageConsole.h>
#include <editor/controls/ImGui/NodeGraph.h>

namespace Engine
{
using ControlPtr = UIBuilder::ControlPtr;

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

}
