// DEPRECATED


#include <catch2/catch_all.hpp>
#include <iostream>

#include <state/store.h>

struct State
{
    int count = 0;
    std::string name = "";
};

struct IncrementAction
{
    int value;
};

struct DecrementAction
{
    int value;
};

struct UpdateNameAction
{
    std::string name;
};

using NumericActions = std::variant<IncrementAction, DecrementAction>;
auto numericReducer = [](State state, NumericActions action)
{
    std::visit([&state](auto&& action)
    {
        using T = std::decay_t<decltype(action)>;

        if constexpr (std::is_same_v<T, IncrementAction>)
        {
            state.count += action.value;
        }
        else if constexpr (std::is_same_v<T, DecrementAction>)
        {
            state.count -= action.value;
        }
        else 
        {
           static_assert(false, "non-exhaustive visitor!");
        }
    }, action);

    return state;
};

using StringActions = std::variant<UpdateNameAction>;
auto stringReducer = [](State state, StringActions action)
{
    std::visit([&state](auto&& action)
    {
        using T = std::decay_t<decltype(action)>;

        if constexpr (std::is_same_v<T, UpdateNameAction>)
        {
            state.name = action.name;
        }
        else 
        {
           static_assert(false, "non-exhaustive visitor!");
        }
    }, action);

    return state;
};

using AllActions = std::variant<NumericActions, StringActions>;

auto mainReducer = [](State state, AllActions action)
{
    std::visit([&state](auto&& action)
    {
        using T = std::decay_t<decltype(action)>;

        if constexpr (std::is_same_v<T, StringActions>)
        {
            state = stringReducer(state, action);
        }
        else if constexpr (std::is_same_v<T, NumericActions>)
        {
            state = numericReducer(state, action);
        }
        else 
        {
           static_assert(false, "non-exhaustive visitor!");
        }
    }, action);

    return state;
};

TEST_CASE("Subscribe to Global State Changes", "[STORE]") 
{
    int callCount = 0;

    Forged::State::Store store(State{ 0, "MyOldName"}, mainReducer);

    store.subscribeToState([&callCount](State state)
    {
        callCount++;
    });

    store.dispatch(IncrementAction{ 4 });
    store.dispatch(UpdateNameAction{ "MyNewName" });
    store.dispatch(DecrementAction{ 1 });

    REQUIRE(store.getState().count == 3);
    REQUIRE(store.getState().name == "MyNewName");
    REQUIRE(callCount == 3);
}

auto countSelector = [](const State& state) -> int
{
    return state.count;
};

auto nameSelector = [](const State& state) -> std::string
{
    return state.name;
};

auto integerPredicate = [](int a, int b)
{
    return a == b;
};

auto stringPredicate = [](const std::string& a, const std::string& b)
{
    return a == b;
};

TEST_CASE("Subscribe to Changes with Previous Value", "[STORE]") 
{
    Forged::State::Store store(State{ }, mainReducer);

    store.subscribeWithPrevious(countSelector, integerPredicate,
        [&](int a, int b)
        {
            // TODO ensure a != b
        });

    store.subscribeWithPrevious(nameSelector, stringPredicate,
        [&](std::string a, std::string b)
        {
            // TODO ensure a != b
        });

    store.dispatch(UpdateNameAction{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
}

TEST_CASE("Subscribe to Slice State Changes", "[STORE]") 
{
    int callCount = 0;

    Forged::State::Store store(State{ }, mainReducer);

    store.subscribeToSlice(countSelector, integerPredicate,
        [&](int count)
        {
            auto state = store.getState();
            callCount++;
        });

    store.subscribeToSlice(nameSelector, stringPredicate,
        [&](std::string name)
        {
            auto state = store.getState();
            callCount++;
        });

    store.dispatch(UpdateNameAction{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
    store.dispatch(UpdateNameAction{ "World" });

    REQUIRE(store.getState().count == 2);
    REQUIRE(store.getState().name == "World");
    REQUIRE(callCount == 5);
}