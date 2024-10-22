#pragma once

#include <imgui.h>
#include <imgui_node_editor.h>

#include <view/UserControl.h>

namespace node = ax::NodeEditor;

namespace Forged::View
{

class NodeGraph : public UserControl
{
public:
    NodeGraph() = default;

    ControlType getType() override { return ControlType::NodeGraph; }
    std::string getName() override { return "NodeGraph"; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    node::EditorContext* m_Context = nullptr;
};

}