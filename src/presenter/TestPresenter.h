#pragma once

#include <presenter/ReactiveProperty.h>

namespace Forged::Presenter
{

class IMainWindow
{
public:
    virtual ReactiveProperty<std::string>& getName() = 0;
};

class TestPresenter : public IMainWindow
{
public:
    ReactiveProperty<int> count;
    ReactiveProperty<std::string> name;

    ReactiveProperty<std::string>& getName() override { return name; }

    TestPresenter()
    : count(10)
    , name("Hello")
    {
        count.bind([](int value)
        {
            std::cout << "Value changed" << value;
        });

        name.bind([](const std::string& value)
        {
            std::cout << "Presenter:: Value changed" << value;
        });   
    }
};

}