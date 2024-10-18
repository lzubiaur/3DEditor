#pragma once
#include <core/IApplication.h>
#include <editor/IUIBuilder.h>
#include <services/IServiceProvider.h>

namespace Engine
{

class UIBuilder : public IUIBuilder
{
public:
    UIBuilder::UIBuilder() = default;

    ControlPtr buildMainMenu(IServiceProvider& services) override;
    ControlPtr buildNodeGraph(IServiceProvider& services) override;
};

}
