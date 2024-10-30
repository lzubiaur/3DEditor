#pragma once

#include <services/IServiceLocator.h>
#include <state/Store.h>
#include <state/Model.h>

namespace Forged::Presenter
{

class IPresenter
{
public:
    virtual ~IPresenter() noexcept = default;

    virtual bool isVisible() = 0;
    virtual void setIsVisible(bool value) = 0;
};

class PresenterBase : public IPresenter
{
public:
    PresenterBase(IServiceLocator& services);

    bool isVisible() { return mVisible; }
    void setIsVisible(bool value) { mVisible = value; }

protected:
    void dispatch(State::Reducer reducer);

protected:
    IServiceLocator& mServices;
    bool mVisible = false;
};

}