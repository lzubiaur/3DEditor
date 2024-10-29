#pragma once

#include <services/EventBus.h>

namespace Forged::Presenter
{

// DEPRECATED
struct UIEvents
{
    // inline static const char* OnButtonClick = "OnButtonClick";
};

namespace Events
{

// TODO use reactive stream instead of signals
enum class LogLevel
{
    Error = 0,
    Warning = 1,
    Info = 2,
};

struct TraceMessageEvent
{
    LogLevel level;
    std::string message;
};

}

}