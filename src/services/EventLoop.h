#pragma once

#include <services/IService.h>

#include <rxcpp/rx.hpp>
#include <any>

namespace Forged
{

class EventLoop : public IService
{
public:
    EventLoop() = default;
    ~EventLoop() noexcept = default;

    void onShutdown() override 
    {
         //TODO
    }

    template <typename Func, typename... Args>
    void execute(Func&& func, Args&&... args) 
    {
        auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

        rxcpp::observable<>::just(0)
            .observe_on(rxcpp::observe_on_run_loop(mLoop))
            .subscribe([task](int) { task(); });
    }

    void update()
    {
        if (!mLoop.empty())
        {
            mLoop.dispatch();
        }
    }

private:
    rxcpp::schedulers::run_loop mLoop;
};

}