#pragma once

#include <rxcpp/rx.hpp>

class Subscription
{
public:
    Subscription() = default;
    Subscription(rxcpp::subscription&& subscription) : mSubscription(std::move(subscription)) {}
    ~Subscription() noexcept = default;

    void unsubscribe()
    {
        mSubscription.unsubscribe();
    }

    bool isSubscribe()
    {
        mSubscription.is_subscribed();
    }

private:
    rxcpp::subscription mSubscription;
};

namespace Forged::Presenter
{

template<typename T>
class ReactiveProperty
{
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