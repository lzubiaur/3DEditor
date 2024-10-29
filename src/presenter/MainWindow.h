#pragma once

namespace Forged::Presenter
{

class IMainWindow
{
public:
    virtual ~IMainWindow() = default;
};

class MainWindow : public IMainWindow
{
public:
    MainWindow() = default;
};

}