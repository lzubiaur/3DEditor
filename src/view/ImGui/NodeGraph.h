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

    ControlHash getHash() override { return ControlHashes::NodeGraphHash; }
    ControlType getType() override { return ControlType::Panel; }
    std::string getName() override { return ControlName::NodeGraph; }

    void onInitialize() override;
    void onShutdown() override;
    void onDraw() override;

private:
    node::EditorContext* m_Context = nullptr;
};

}