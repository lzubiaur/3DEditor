#pragma once

#include <services/IService.h>
#include <spdlog/spdlog.h>

namespace Engine
{

class LogService : public IService
{
public:
    LogService();

    template <typename... Args>
    using fmt = spdlog::format_string_t<Args...>;

    template<typename... Args>
    void error(fmt<Args...> fmt, Args&&... args)
    {
        mLogger.error(fmt, std::forward<Args(args));
    }

    void onShutdown() override;

private:
    void createCustomLogger();

private:
    spdlog::pattern_formatter mFormatter;
    mutable std::shared_ptr<spdlog::logger> mLogger;
};

}