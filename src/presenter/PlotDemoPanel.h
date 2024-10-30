#pragma once

#include <presenter/PresenterBase.h>

namespace Forged::Presenter
{

class IPlotDemoPanel : public PresenterBase
{
public:
    IPlotDemoPanel(IServiceLocator& services) : PresenterBase(services) {}
};

class PlotDemoPanel : public IPlotDemoPanel
{
public:
    PlotDemoPanel(IServiceLocator& services);

    void setIsVisible(bool value);
};

}