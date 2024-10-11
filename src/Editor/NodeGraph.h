#pragma once

#include <imgui.h>
#include <imgui_node_editor.h>

#include <Editor/IUIControl.h>

namespace node = ax::NodeEditor;

namespace Engine 
{

class NodeGraph : public IUIControl
{
public:
    NodeGraph();
    ~NodeGraph();

    virtual bool onInitialize() override;
    virtual void onDraw() override;

private:
    node::EditorContext* m_Context = nullptr;
};

}