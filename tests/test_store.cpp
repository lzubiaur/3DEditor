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

TEST_CASE("Subscribe to global state changes", "[STORE]") 
{
    int callCount = 0;

    Forge::State::Store store(State{ 0, "MyOldName"});

    store.subscribeGlobal([&callCount](State state)
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

TEST_CASE("Testing old new", "[STORE]") 
{
    Forge::State::Store store(State{ });

    store.subscribePairWise(countSelector,
    [&](int a, int b)
    {
        auto state = store.getState();
    },
    [](int a, int b)
    {
        return a == b;
    });

    store.subscribePairWise(nameSelector, 
    [&](std::string a, std::string b)
    {
        auto state = store.getState();
    },
    [](std::string a, std::string b)
    {
        return a == b;
    });

    store.dispatch(UpdateName{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
}

TEST_CASE("Subscribe to local state changes", "[STORE]") 
{
    int callCount = 0;

    Forge::State::Store store(State{ });

    store.subscribe(countSelector, [&](int count)
    {
        auto state = store.getState();
        callCount++;
    }, 
    [](int a, int b)
    {
        return a == b;
    });

    store.subscribe(nameSelector, [&](std::string name)
    {
        auto state = store.getState();
        callCount++;
    },
    [](std::string a, std::string b)
    {
        return a == b;
    });

    store.dispatch(UpdateName{ "Hello" });
    store.dispatch(IncrementAction{ 2 });
    store.dispatch(UpdateName{ "World" });

    REQUIRE(store.getState().count == 2);
    REQUIRE(store.getState().name == "World");
    REQUIRE(callCount == 5);
}