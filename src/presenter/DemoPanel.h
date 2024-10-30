#pragma once

#include <presenter/PresenterBase.h>

namespace Forged::Presenter
{

class IDemoPanel : public PresenterBase
{
public:
    IDemoPanel(IServiceLocator& services) : PresenterBase(services) {}
};

class DemoPanel : public IDemoPanel
{
public:
    DemoPanel(IServiceLocator& services);

    void setIsVisible(bool value);
};

}