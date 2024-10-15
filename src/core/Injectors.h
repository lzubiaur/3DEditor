#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Platform.h>
#include <editor/UIRenderer.h>
#include <editor/IUIRenderer.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Engine
{
    auto getApplicationInjector()
    {
        // return di::make_injector(
        //     di::bind<int>().to(600),
        //     di::bind<IApplication>().to<Application>(),
        //     di::bind<IPlatform>().to<Platform>(),
        //     di::bind<IUIRenderer>().to<UIRenderer>(),
        //     di::bind<IManager*[]>().to<ScriptManager, UIManager>()
        // );

        return di::make_injector(
            di::bind<int>().to(600),
            di::bind<IPlatform>().to<Platform>(),
            di::bind<IApplication>().to<Application>(),
            di::bind<IUIRenderer>().to<UIRenderer>(),
            di::bind<IManager*[]>().to<ScriptManager>()
        );
    }
}