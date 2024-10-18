#pragma once

#include <services/LogService.h>
#include <services/SignalService.h>

namespace Engine
{
    
class IServiceLocator
{
public:
    virtual ~IServiceLocator() noexcept = default;

    virtual SignalService& getSignalService() = 0;
    virtual LogService& getLogService() = 0; 
};
    
}