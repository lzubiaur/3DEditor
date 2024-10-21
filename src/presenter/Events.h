#pragma once

#include <services/EventBus.h>

// TODO should probably remove signal and use ReactiveCommand instead

namespace Forged::Presenter
{

// TODO rename
struct UIEvents
{
    inline static const char* OnRequestAppClose = "OnRequestAppClose";
    inline static const char* OnWindowResized = "OnWindowResized";
    inline static const char* OnButtonClick = "OnButtonClick";
};

namespace Events
{

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