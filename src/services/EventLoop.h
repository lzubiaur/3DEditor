#pragma once

#include <services/IService.h>

#include <rxcpp/rx.hpp>
#include <any>
#include <functional>
#include <chrono>

namespace Forged
{

class IEventLoop : public IService
{
public:
    using Func = std::function<void()>;
    using Milliseconds = std::chrono::milliseconds;
    using TimePoint = std::chrono::steady_clock::time_point;

    virtual void immediate(Func&& func) = 0;
    virtual void timeout(Func&& func, Milliseconds when) = 0;

    virtual void interval(Func&& func, Milliseconds period) = 0;
    virtual void interval(Func&& func, Milliseconds period, TimePoint start) = 0;
};

class IEventLoopInternal : public IEventLoop
{
public:
    virtual void update() = 0;
};

class EventLoop : public IEventLoopInternal
{
public:
    void onShutdown() override;

    void immediate(Func&& func) override;
    void timeout(Func&& func, Milliseconds when) override;

    void interval(Func&& func, Milliseconds period) override ;
    void interval(Func&& func, Milliseconds period, TimePoint start) override;

    void update() override;

private:
    rxcpp::schedulers::run_loop mLoop;
};

}