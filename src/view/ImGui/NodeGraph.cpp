#include <view/ImGui/NodeGraph.h>

#include <imgui.h>

namespace ed = ax::NodeEditor;

namespace Forged::View
{

NodeGraph::NodeGraph()
: mOpen(true)
{
}

NodeGraph::~NodeGraph()
{
}

void NodeGraph::onInitialize()
{
    ed::Config config;
    config.SettingsFile = "NodeGraphConfig.json";
    m_Context = ed::CreateEditor(&config);
}

void NodeGraph::onShutdown() 
{
}

void NodeGraph::onDraw()
{
    if (!mOpen)
    {
        return;
    }

    ed::SetCurrentEditor(m_Context);
    ed::Begin("Node Graph", ImVec2(0.0, 0.0f));

    int uniqueId = 1;

    ed::BeginNode(uniqueId++);
        ImGui::Text("Node A");
        ed::BeginPin(uniqueId++, ed::PinKind::Input);
            ImGui::Text("In");
        ed::EndPin();
        ImGui::SameLine();
        ed::BeginPin(uniqueId++, ed::PinKind::Output);
            ImGui::Text("Out");
        ed::EndPin();
    ed::EndNode();

    ed::BeginNode(uniqueId++);
        ImGui::Text("Node B");
        ed::BeginPin(uniqueId++, ed::PinKind::Input);
            ImGui::Text("In");
        ed::EndPin();
        ImGui::SameLine();
        ed::BeginPin(uniqueId++, ed::PinKind::Output);
            ImGui::Text("Out");
        ed::EndPin();
    ed::EndNode();

    ed::End();
    ed::SetCurrentEditor(nullptr);
}
}
