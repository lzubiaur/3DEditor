#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Application.h>
#include <core/Platform.h>
#include <editor/view/ImGui/UIRenderer.h>
#include <editor/view/ImGui/UIBuilder.h>
#include <services/ReactiveService.h>
#include <editor/IUIRenderer.h>
#include <editor/IUIBuilder.h>
#include <editor/presenter/TestPresenter.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Engine::Core
{

class Injector
{
public:
    static inline auto getManagerInjector(IApplication& app)
    {
        return di::make_injector(
            di::bind<IUIRenderer>().to<UIRenderer>(),
            di::bind<IUIBuilder>().to<UIBuilder>(),
            di::bind<IPlatform>().to<Platform>(),
            di::bind<IReactiveService>().to<ReactiveService>(),
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
            di::bind<Presenter::IMainWindow>().to<Presenter::TestPresenter>()
        );
    }
};

}