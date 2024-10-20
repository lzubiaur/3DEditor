#pragma once

#include <services/LogService.h>
#include <services/SignalService.h>
#include <services/IReactiveService.h>
#include <services/EventBus.h>

namespace Forged
{

class IServiceLocator
{
public:
    virtual ~IServiceLocator() noexcept = default;

    virtual SignalService& getSignalService() = 0;
    virtual LogService& getLogService() = 0;
    virtual IReactiveService& getReactiveService() = 0;
    virtual EventBus& getEventBus() = 0;
};
    
}