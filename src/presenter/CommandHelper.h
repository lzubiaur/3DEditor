#pragma once

namespace Forged::Presenter::Command
{

#define BEGIN_COMMAND(name) \
struct name##CommandArgument : public CommandArgument<name##CommandType> {

#define END_COMMAND(name) \
}; \
using name##Command = ReactiveCommand<name##CommandArgument>;

#define COMMAND(name) \
BEGIN_COMMAND(name) \
END_COMMAND(name)

#define COMMAND_TYPE(name, ...) \
enum class name##CommandType { \
    __VA_ARGS__ \
};

template<typename T>
struct CommandArgument
{
    T type;
};

}
