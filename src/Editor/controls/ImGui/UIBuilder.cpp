#include <editor/controls/ImGui/UIBuilder.h>
#include <editor/controls/ImGui/MainMenu.h>
#include <editor/controls/ImGui/NodeGraph.h>

namespace Engine
{
using ControlPtr = UIBuilder::ControlPtr;

ControlPtr UIBuilder::buildMainMenu(IServiceProvider& services)
{
    return std::make_shared<MainMenu>(services);
}

ControlPtr UIBuilder::buildNodeGraph(IServiceProvider& services)
{
    return std::make_shared<NodeGraph>();
}

}
