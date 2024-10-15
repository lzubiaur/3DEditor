#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Application.h>
#include <core/Platform.h>
#include <editor/UIRenderer.h>
#include <editor/IUIRenderer.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Engine
{
    auto getManagerInjector(IApplication& app)
    {
        return di::make_injector(
            di::bind<IUIRenderer>().to<UIRenderer>(),
            di::bind<IPlatform>().to<Platform>(),
            di::bind<IApplication>().to<Application>(app)
        );
    }

    auto getApplicationInjector()
    {
        return di::make_injector(
            di::bind<IPlatform>().to<Platform>()
            // di::bind<IApplication>().to<Application>().in(di::singleton)
        );
    }
}