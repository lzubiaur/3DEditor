#pragma once

#include <presenter/state/Actions.h>
#include <presenter/state/Model.h>

#include <rxcpp/rx.hpp>
#include <variant>
#include <utility>

namespace Forge::State
{

/**
 * @class Store
 * @brief Manages a global state container with subscription-based updates.
 * 
 * The `Store` class centralizes the application's global state and provides
 * methods for state retrieval, updating via dispatched actions, and broadcasting
 * updates to subscribers. This class follows the Redux pattern, where actions
 * represent state transitions, and subscribers can register callbacks to react 
 * to state changes. It is using templates to manage any specified state type, 
 * and leverages the `rxcpp` library to handle asynchronous state updates.
 * 
 * @tparam StateT The type of state managed by the store.
 */

template<typename StateT>
class Store
{
public:

    /**
     * @brief Constructs the Store with an initial state.
     * @param initial The initial state of type `StateT`.
     */
    Store(StateT initial) : mState(initial)
    {
    }

    /**
     * @brief Retrieves the current state.
     * @return The current state of type `StateT`.
     */
    StateT getState() const 
    {
        return mState; 
    }

    /**
     * @brief Resets the state to a specified value.
     * 
     * Sets the global state to a new value and optionally broadcasts the change if 
     * the state differs.
     * @param newState The new state to be set.
     */
    void resetState(const StateT& newState)
    {
        mState = newState; 
        // TODO broadcast new state if changed?
    }

    /**
     * @brief Dispatches an action to modify the state.
     * 
     * Applies a reducer function to the current state with the provided action, 
     * then broadcasts the new state to all subscribers.
     * @tparam Action Type of the action to be dispatched.
     * @param action The action used to update the state.
     */
    template<typename Action>
    void dispatch(Action action)
    {
        mState = reduce(mState, action);
        stream.get_subscriber().on_next(mState);
    }

    /**
     * @brief Subscribes to changes in the entire state.
     *
     * Registers a callback that triggers whenever the global state updates,
     * providing the latest state value to the subscriber.
     *
     * @param callback Function invoked with the updated state.
     * @return Subscription handle for managing the subscription.
     */

    // TODO usage OnError and OnComplete parameters instead of variadic parameters.
    template <typename... ArgN>
    auto subscribeToState(std::function<void(StateT)> observer, ArgN &&...an)
    {
        return stream.get_observable().subscribe(observer, std::forward<ArgN>(an)...);
    }

    template <typename Func>
    using ReturnType = decltype(std::declval<Func>()(std::declval<StateT &>()));

    template<typename T>
    using Observer = std::function<void(ReturnType<T>)>;

    template<typename T>
    using Predicate = std::function<bool(ReturnType<T>, ReturnType<T>)>;

    /**
     * @brief Subscribes to changes in a specific slice of the state.
     *
     * Registers a callback that triggers when the selected slice of state changes,
     * notifying only on updates relevant to the specified slice.
     *
     * @param sliceSelector Function to select the slice within the state.
     * @param callback Function invoked with the updated slice value.
     * @return Subscription handle for managing the subscription.
     */
    template<typename Selector>
    auto subscribeToSlice(Selector selector, Predicate<Selector> predicate, Observer<Selector> observer)
    {
        return stream.get_observable()
            .start_with(mState)
            .map(selector)
            .distinct_until_changed(predicate)
            .subscribe(observer);
    }
    
    // TODO Create a SubscribeMetadata to pass as parameters with 
    // the Selector, Observer, Predicate, OnError and OnComplete callback

    template<typename T>
    using ObserverOldNew = std::function<void(ReturnType<T>, ReturnType<T>)>;

    /**
     * @brief Subscribes to a specific slice of state with previous and new values.
     *
     * Registers a callback that triggers on changes in the selected slice,
     * providing both the previous and current values for comparison.
     *
     * @param selector Function to select the slice within the state.
     * @param observer Function invoked with a pair of previous and current slice values.
     * @param predicate Function that compares previous and current slice values to filter updates.
     * @return Subscription handle for managing the subscription.
     */
    template<typename Selector>
    auto subscribeWithPrevious(Selector selector, Predicate<Selector> predicate, ObserverOldNew<Selector> observer)
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