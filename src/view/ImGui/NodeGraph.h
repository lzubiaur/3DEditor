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

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    node::EditorContext* m_Context = nullptr;
};

}