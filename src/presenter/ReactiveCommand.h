#pragma once
#include <presenter/ReactiveProperty.h>

#include <rxcpp/rx.hpp>

namespace Forged::Presenter
{

// TODO create a timeout command

template<typename T>
class ReactiveCommand
{
public:
    ReactiveCommand() = default;
    ~ReactiveCommand() noexcept
    {
        mSubject.get_subscriber().on_completed();
    }

    void execute(T arg)
    {
        mSubject.get_subscriber().on_next(arg);
    }

    Subscription bind(const std::function<void(T)>& onNext)
    {
        return { mSubject.get_observable().subscribe(onNext) };
    }

    void unbind(Subscription& binding)
    {
        binding.unsubscribe();
    }

private:
     rxcpp::subjects::subject<T> mSubject;
};

}