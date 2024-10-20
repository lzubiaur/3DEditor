#pragma once

#include <rxcpp/rx.hpp>

// TODO move to more appropirate folder

namespace Forged::Presenter
{

template<typename T>
class ReactiveProperty
{
public:
    // TODO create wrapper
    using Subscription = rxcpp::subscription;

public:
    ReactiveProperty(T value) : mValue(value) {}

    // Add reference and move
    void setValue(T value)
    {
        mValue = value;
        notifyValueChanged(value);
    }

    T getValue()
    {
        return mValue;
    }

    Subscription bind(const std::function<void(T)>& onNext)
    {
        return { mSubject.get_observable().subscribe(onNext) };
    }

    void unbind(const Subscription& binding)
    {
        binding.subscription.unsubscribe();
    }

private:
    void notifyValueChanged(T value)
    {
        mSubject.get_subscriber().on_next(value);
    }

private:
    T mValue;
    rxcpp::subjects::subject<T> mSubject;
};

}