#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Application.h>
#include <core/Platform.h>
#include <view/ImGui/UIRenderer.h>
#include <view/ImGui/UIBuilder.h>
#include <services/ReactiveService.h>
#include <services/EventLoop.h>
#include <view/IUIRenderer.h>
#include <view/IUIBuilder.h>
#include <presenter/TestPresenter.h>
#include <presenter/MessagePanel.h>
#include <presenter/MainMenu.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Forged::Core
{

using namespace Forged;

class Injector
{
public:
    static inline auto getManagerInjector(IApplication& app)
    {
        return di::make_injector(
            di::bind<View::IUIRenderer>().to<View::UIRenderer>(),
            di::bind<View::IUIBuilder>().to<View::UIBuilder>(),
            di::bind<IPlatform>().to<Platform>(),
            di::bind<IReactiveService>().to<ReactiveService>(),
            di::bind<IEventLoopInternal>().to<EventLoop>(),
            di::bind<IApplication>().to<Application>(app)
        );
    }

    static inline auto getApplicationInjector()
    {
        return di::make_injector(
            di::bind<IPlatform>().to<Platform>()
        );
    }

    static inline auto getUIControlInjector(IServiceLocator& services)
    {
        return di::make_injector(
            di::bind<IServiceLocator>().to(services),
            di::bind<Presenter::IMainWindow>().to<Presenter::TestPresenter>(),
            di::bind<Presenter::IMainMenu>().to<Presenter::MainMenu>(),
            di::bind<Presenter::IMessagePanel>().to<Presenter::MessagePanel>()
        );
    }
};

}