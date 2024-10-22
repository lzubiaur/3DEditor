#pragma once

#include <view/UserControl.h>
#include <services/IServiceLocator.h>
#include <imgui.h>

namespace Forged::View
{
class ImGuiDemo : public UserControl
{
public:
    ImGuiDemo() : UserControl() 
    {
        mOpen = false;
    }

    ControlType getType() override { return ControlType::None; }
    std::string getName() override { return "ImGuiDemo"; }

    void onInitialize() override {}
    void onShutdown() override {}
    void onDraw() override 
    {
        if (mOpen)
        {
            ImGui::ShowDemoWindow();
        }
    }
};

}