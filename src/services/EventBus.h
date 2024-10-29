#pragma once

#include <memory>
#include <string>
#include <services/IService.h>
#include <rxcpp/rx.hpp>
#include <any>

namespace Forged
{

// DEPRECATED
// WARN : probably not very efficient if too much events

class EventBus : public IService
{
public:
    void onShutdown() {}

    template<typename EventType>
    rxcpp::observable<EventType> getEvent() 
    {
        return mBus.get_observable()
            .filter([](std::any event) { return std::any_cast<EventType>(&event) != nullptr; })
            .map([](std::any event) { return std::any_cast<EventType>(event); });
    }

    template<typename EventType>
    void emitEvent(const EventType& event) 
    {
        mBus.get_subscriber().on_next(event);
    }

private:
    rxcpp::subjects::subject<std::any> mBus;
};

}