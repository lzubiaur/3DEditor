#pragma once

#include <imgui.h>
#include <imgui_node_editor.h>

#include <editor/IControl.h>

namespace node = ax::NodeEditor;

namespace Engine 
{

class NodeGraph : public IControl
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