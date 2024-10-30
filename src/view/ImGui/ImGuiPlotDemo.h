#pragma once

#include <view/UserControl.h>
#include <services/IServiceLocator.h>
#include <presenter/PlotDemoPanel.h>
#include <imgui.h>
#include <implot.h>

namespace Forged::View
{
class ImGuiPlotDemo : public UserControl
{
public:
    ImGuiPlotDemo(Presenter::IPlotDemoPanel& presenter)
    : UserControl()
    , mPresenter(presenter)
    {
        mOpen = false;
    }

    ControlHash getHash() override { return ControlHashes::PlotDemoPanelHash; }
    ControlType getType() override { return ControlType::Panel; }
    std::string getName() override { return ControlName::PlotDemoPanel; }

    void onInitialize() override
    {
        ImPlot::CreateContext();
    }

    void onShutdown() override {}

    void onDraw() override 
    {
        if (!mPresenter.isVisible())
        {
            return;
        }

        mOpen = true;
        ImPlot::ShowDemoWindow(&mOpen);

        if (!mOpen)
        {
            mPresenter.setIsVisible(false);
        }
    }

private:
    Presenter::IPlotDemoPanel& mPresenter;
};

}