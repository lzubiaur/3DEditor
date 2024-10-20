#pragma once

#include <memory>
#include <string>
#include <services/IService.h>
#include <rxcpp/rx.hpp>
#include <any>

namespace Forged
{

class IReactiveService : public IService
{
public:
    using LogMessageSlot = std::function<void(const std::string&)>;

    virtual void onLogMessage(const std::string& message) = 0;
    virtual void subscribeToLogMessage(const LogMessageSlot& slot) = 0;
};

}