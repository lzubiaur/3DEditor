#pragma once

#include <presenter/state/Actions.h>
#include <presenter/state/Model.h>

#include <rxcpp/rx.hpp>
#include <variant>
#include <utility>

namespace Forge::State
{

template<typename StateT>
class Store
{
public:
    Store(StateT initial) : mState(initial)
    {
    }

    StateT getState() const { return mState; }

    void resetState(const StateT& newState)
    {
        mState = newState; 
        // TODO broadcast new state if changed?
    }

    template<typename Action>
    void dispatch(Action action)
    {
        mState = reduce(mState, action);
        stream.get_subscriber().on_next(mState);
    }

    /**
     * Subscribe to changes on the global state
     * Arguments: onNext, onError and onComplete callbacks
     */
    template<typename... ArgN>
    void subscribeGlobal(std::function<void(StateT)> observer, ArgN&&... an)
    {
        stream.get_observable().subscribe(observer, std::forward<ArgN>(an)...);
    }

    /**
     * Subscribes to local state changes. The observer is immediately 
     * invoked with the current state upon subscription.
     *
     * Parameters:
     * - selector: extracts and filters a specific portion of the state.
     * - observer: invoked when the selected state changes.
     * - predicate: compares an item against its immediate predecessor for distinctness
     */
    template<typename Func>
    using ReturnType = decltype(std::declval<Func>()(std::declval<StateT&>()));

    template<typename T>
    using Observer = std::function<void(ReturnType<T>)>;

    template<typename T>
    using Predicate = std::function<bool(ReturnType<T>, ReturnType<T>)>;

    template<typename Selector>
    auto subscribe(Selector selector, Observer<Selector> observer, Predicate<Selector> predicate)
    {
        return stream.get_observable()
            .start_with(mState)
            .map(selector)
            .distinct_until_changed(predicate)
            .subscribe(observer);
    }

    template<typename T>
    using ObserverOldNew = std::function<void(ReturnType<T>, ReturnType<T>)>;

    template<typename Selector>
    auto subscribePairWise(Selector selector, ObserverOldNew<Selector> observer, Predicate<Selector> predicate)
    {
        return stream.get_observable()
            .start_with(mState)
            .map(selector)
            .distinct_until_changed(predicate)
            .pairwise()
            .subscribe([observer](auto tuple)
            {
                observer(std::get<0>(tuple), std::get<1>(tuple));
            });
    }

    template<typename Selector>
    auto subscribe(Selector selector, Observer<Selector> observer)
    {
        return stream.get_observable()
            .map(selector)
            .distinct_until_changed()
            .subscribe(observer);
    }

private:

    // AppState reduce(AppState& model, const Actions::PanelAction &action)
    // {
    //     std::visit([&model](const auto &msg)
    //     {
    //     using T = std::decay_t<decltype(msg)>;

    //     if constexpr (std::is_same_v<T, Actions::AddObject>) 
    //     {
    //         model.panels.push_back(Model::Panel{msg.id, true, ""});
    //     }
    //     else if constexpr (std::is_same_v<T, Actions::RemoveObject>) 
    //     {
    //         model.panels.erase(
    //             std::remove_if(model.panels.begin(), model.panels.end(),
    //                            [&](const Model::Panel& panel) { return panel.id == msg.id; }),
    //             model.panels.end());
    //     }
    //     else if constexpr (std::is_same_v<T, Actions::GetObject>)
    //     {
            
    //     }
    //     else if constexpr (std::is_same_v<T, Actions::UpdateTitle>) 
    //     {

    //     }
    //     else if constexpr (std::is_same_v<T, Actions::UpdateVisibility>) 
    //     {

    //     } }, action);

    //     return model;
    // }

private:
    StateT mState;
    rxcpp::subjects::subject<StateT> stream;
};
}