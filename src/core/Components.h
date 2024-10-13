#pragma once

#include <managers/ScriptManager.h>
#include <managers/UIManager.h>
#include <core/Platform.h>

#include <memory>
#include <boost/di.hpp>
namespace di = boost::di;

namespace Engine
{
    auto getApplicationInjector()
    {
        return di::make_injector(
            di::bind<int>().to(600),
            di::bind<IManager*[]>().to<ScriptManager, UIManager>()
        );
    }
}