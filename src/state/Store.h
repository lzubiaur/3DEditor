#pragma once

#include <state/Model.h>

#include <rxcpp/rx.hpp>
#include <variant>
#include <utility>
#include <exception>

namespace Forged::State
{

template<typename StateT>
class Store
{
public:
    using StateObserver = std::function<void (const StateT&)>;
    using Reducer = std::function<StateT(const StateT&)>;

    Store(StateT initial)
    : mState(initial)
    {
        mObservable = mStream
            .get_observable()
            .start_with(nilReducer)    // Emit an initial default value before other data
            .map(reduce)               // Transform each emitted item using the 'reduce' function
            .publish()                 // Convert to a hot observable, sharing data among subscribers
            .as_dynamic();             // Enable dynamic, real-time updates for all subscribers
    }

    void startEmitting()
    {
        mObservable.connect();
    }

    const StateT& getState() const 
    {
        return mState; 
    }

    void dispatch(Reducer reducer)
    {
        mStream.get_subscriber().on_next(reducer);
    }

    auto subscribeToState(StateObserver observer)
    {
        return mObservable.subscribe(observer);
    }

    template <typename Func>
    using ReturnType = decltype(std::declval<Func>()(std::declval<StateT &>()));

    template<typename T>
    using SliceObserver = std::function<void(ReturnType<T>)>;

    template<typename T>
    using Predicate = std::function<bool(ReturnType<T>, ReturnType<T>)>;

    template<typename Selector>
    auto subscribeToSlice(Selector selector, Predicate<Selector> predicate, SliceObserver<Selector> observer)
    {
        return mObservable
            .map(selector)
            .distinct_until_changed(predicate)
            .subscribe(observer);
    }

    template<typename T>
    using ObserverOldNew = std::function<void(ReturnType<T>, ReturnType<T>)>;

    template<typename Selector>
    auto subscribeWithPrevious(Selector selector, Predicate<Selector> predicate, ObserverOldNew<Selector> observer)
    {
        return mObservable
            .map(selector)
            .distinct_until_changed(predicate)
            .pairwise()
            .subscribe([observer](auto tuple)
            {
                observer(std::get<0>(tuple), std::get<1>(tuple));
            });
    }

private:

    std::function<StateT(Reducer)> reduce = [&](Reducer reducer) -> StateT
    {
        mState = reducer(mState);
        return mState;
    };

    Reducer nilReducer = [&](const StateT &state) -> StateT
    {
        return mState;
    };

private:
    StateT mState;
    rxcpp::connectable_observable<StateT> mObservable;
    rxcpp::subjects::subject<Reducer> mStream;
};

}