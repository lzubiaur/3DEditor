#include <catch.hpp>
#include <iostream>

#include <presenter/state/store.h>

struct State
{
    int count = 0;
    std::string name = "";
};

struct IncrementAction
{
    int value;
};

struct UpdateName
{
    std::string name;
};

State reduce(State state, IncrementAction action)
{
    state.count = state.count + action.value;
    return state;
}

State reduce(State state, UpdateName action)
{
    state.name = action.name;
    return state;
}

TEST_CASE("Subscribe to Global State Changes", "[STORE]") 
{
    int callCount = 0;

    Forge::State::Store store(State{ 0, "MyOldName"});

    store.subscribeToState([&callCount](State state)
    {
        callCount++;
    });

    store.dispatch(IncrementAction{ 2 });
    store.dispatch(UpdateName{ "MyNewName" });

    REQUIRE(store.getState().count == 2);
    REQUIRE(store.getState().name == "MyNewName");
    REQUIRE(callCount == 2);
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
    Forge::State::Store store(State{ });

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

    store.dispatch(UpdateName{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
}

TEST_CASE("Subscribe to Slice State Changes", "[STORE]") 
{
    int callCount = 0;

    Forge::State::Store store(State{ });

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

    store.dispatch(UpdateName{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
    store.dispatch(UpdateName{ "World" });

    REQUIRE(store.getState().count == 2);
    REQUIRE(store.getState().name == "World");
    REQUIRE(callCount == 5);
}