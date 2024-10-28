#include <catch2/catch_all.hpp>
#include <state/store.h>
#include <iostream>

// -------------------- State -----------------------

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

// ------------------- Selectors -------------------------

auto countSelector = [](const State& state) -> int
{
    return state.count;
};

auto nameSelector = [](const State& state) -> std::string
{
    return state.name;
};

auto integerPredicate = [](int a, int b) -> bool
{
    return a == b;
};

auto stringPredicate = [](const std::string& a, const std::string& b)-> bool
{
    return a == b;
};

// ------------------- Actions -------------------------

auto Increment = [](State& state)
{
    state.count++;
    return state;
};

// ------------------- Tests -------------------------

TEST_CASE("Subscribe to Global State Changes", "[STORE]") 
{
    int callCount = 0;

    Forged::State::Store store(State{ 0, "MyOldName"});

    store.subscribeToState([&callCount](State state)
    {
        callCount++;
    });

    store.dispatch(Increment);

    store.dispatch([](State& state)
    {
        state.name = "new name";
        return state;
    });

    REQUIRE(callCount == 2);
    REQUIRE(store.getState().count == 1);
    REQUIRE(store.getState().name == "new name");
}

TEST_CASE("Subscribe to Slice State Changes", "[STORE]") 
{
    int callCount = 0;

    Forged::State::Store store(State{});

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

    store.dispatch(Increment);
    store.dispatch([](State& state)
    {
        state.name = "Hello";
        return state;
    });

    REQUIRE(store.getState().count == 2);
    REQUIRE(store.getState().name == "Hello");
    REQUIRE(callCount == 5);
}

TEST_CASE("Subscribe to Changes with Previous Value", "[STORE]") 
{
    Forged::State::Store store(State{});
    bool countChanged = false;
    bool stringChanged = false;

    store.subscribeWithPrevious(countSelector, integerPredicate,
        [&](int a, int b)
        {
            countChanged = a != b;
        });

    store.subscribeWithPrevious(nameSelector, stringPredicate,
        [&](std::string a, std::string b)
        {
            stringChanged = a != b;
        });

    store.dispatch(Increment);
    store.dispatch([](State& state)
    {
        state.name = "Hello";
        return state;
    });

    REQUIRE(store.getState().name == "Hello");
    REQUIRE(countChanged);
    REQUIRE(stringChanged);
}