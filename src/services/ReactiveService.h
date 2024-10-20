#pragma once

#include <memory>
#include <string>
#include <services/IReactiveService.h>
#include <rxcpp/rx.hpp>

namespace Engine
{

class ReactiveService : public IReactiveService
{
public:
    void onShutdown() override {}
    
    void onLogMessage(const std::string& message)
    {
       logMessageSubject.get_subscriber().on_next(message); 
    }

    void subscribeToLogMessage(const LogMessageSlot& subscriber)
    {
        auto subscription = logMessageSubject.get_observable().subscribe(subscriber);
    }
    
private:
    rxcpp::subjects::subject<std::string> logMessageSubject;
    rxcpp::subjects::subject<bool> showMessagesWindow;

};

}