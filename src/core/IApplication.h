#pragma once

#include <core/ISystem.h>
#include <core/IPlatform.h>
#include <state/Store.h>
#include <state/Model.h>
#include <services/LogService.h>

namespace Forged
{

class IApplication
{
public:
    using Store = State::Store<State::AppState>;
    using SystemPtr = std::shared_ptr<ISystem>;

    virtual void addSystem(SystemPtr system) = 0;
    virtual void removeSystem(SystemPtr system) = 0;

    virtual const IPlatform& getPlatform() const = 0;
    
    virtual bool isRunning() = 0;
    virtual void close() = 0;

    virtual Store& getStore() = 0;
    virtual LogService& getLogService() = 0;
};

}