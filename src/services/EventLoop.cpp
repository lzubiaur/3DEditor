#pragma once

#include <services/EventLoop.h>

namespace Forged
{

void EventLoop::onShutdown()
{
}

void EventLoop::immediate(Func&& func)
{
    auto task = std::move(func);

    rxcpp::observable<>::just(0)
        .observe_on(rxcpp::observe_on_run_loop(mLoop))
        .subscribe([task](int)
                   { task(); });
}

void EventLoop::timeout(Func &&func, Milliseconds when)
{
    auto task = std::move(func);

    rxcpp::observable<>::timer(when)
        .observe_on(rxcpp::observe_on_run_loop(mLoop))
        .subscribe([task](int)
                   { task(); });
}

void EventLoop::interval(Func &&func, Milliseconds period)
{
    auto task = std::move(func);

    rxcpp::observable<>::interval(period)
        .observe_on(rxcpp::observe_on_run_loop(mLoop))
        .subscribe([task](int)
                   { task(); });
}

void EventLoop::interval(Func &&func, Milliseconds period, TimePoint start)
{
    auto task = std::move(func);

    rxcpp::observable<>::interval(start, period)
        .observe_on(rxcpp::observe_on_run_loop(mLoop))
        .subscribe([task](int)
                   { task(); });
}

void EventLoop::update()
{
    if (!mLoop.empty())
    {
        mLoop.dispatch();
    }
}

}