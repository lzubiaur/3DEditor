#pragma once

#include <presenter/PresenterBase.h>
#include <services/IServiceLocator.h>
#include <state/Store.h>
#include <state/Model.h>

namespace Forged::Presenter
{

class IMessagePanel : public PresenterBase
{
public:
    IMessagePanel(IServiceLocator& services) : PresenterBase(services) {}
};

class MessagePanel : public IMessagePanel
{
public:
    MessagePanel(IServiceLocator& services);

    void setIsVisible(bool value) override;
};

}