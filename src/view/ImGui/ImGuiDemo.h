#pragma once

#include <view/UserControl.h>
#include <services/IServiceLocator.h>
#include <presenter/DemoPanel.h>
#include <imgui.h>

namespace Forged::View
{
class ImGuiDemo : public UserControl
{
public:
    ImGuiDemo(Presenter::IDemoPanel& presenter)
    : UserControl()
    , mPresenter(presenter)
    {
        mOpen = false;
    }

    ControlType getType() override { return ControlType::None; }
    std::string getName() override { return "DemoPanel"; }

    void onInitialize() override {}
    void onShutdown() override {}
    void onDraw() override 
    {
        if (!mPresenter.isVisible())
        {
            return;
        }

        mOpen = true;

        ImGui::ShowDemoWindow(&mOpen);

        if (!mOpen)
        {
            mPresenter.setIsVisible(false);
        }
    }

private:
    Presenter::IDemoPanel& mPresenter;
};

}