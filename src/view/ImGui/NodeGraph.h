#pragma once

#include <imgui.h>
#include <imgui_node_editor.h>

#include <view/IUIControl.h>

namespace node = ax::NodeEditor;

namespace Forged::View
{

class NodeGraph : public IUIControl
{
public:
    NodeGraph();
    ~NodeGraph();

    ControlType getType() override { return ControlType::NodeGraph; }
    std::string getName() override { return "NodeGraph"; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

    // TODO implement that in a base class UserControl
    bool isVisible() override { return mOpen; }
    void show() override { mOpen = true; }
    void hide() override { mOpen = false; }

private:
    bool mOpen;
    node::EditorContext* m_Context = nullptr;
};

}