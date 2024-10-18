#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Application.h>
#include <core/Platform.h>
#include <editor/controls/ImGui/UIRenderer.h>
#include <editor/controls/ImGui/UIBuilder.h>
#include <editor/IUIRenderer.h>
#include <editor/IUIBuilder.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Engine
{
    auto getManagerInjector(IApplication& app)
    {
        return di::make_injector(
            di::bind<IUIRenderer>().to<UIRenderer>(),
            di::bind<IUIBuilder>().to<UIBuilder>(),
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