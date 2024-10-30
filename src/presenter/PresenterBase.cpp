#pragma once

#include <presenter/PresenterBase.h>

namespace Forged::Presenter
{

PresenterBase::PresenterBase(IServiceLocator& services)
: mServices(services)
, mVisible(true)
{}

void PresenterBase::dispatch(State::Reducer reducer)
{
      mServices.getUIService().getStore().dispatch(reducer);
}

}