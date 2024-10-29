#pragma once

#include <services/IService.h>
#include <rxcpp/rx.hpp>
#include <spdlog/spdlog.h>

namespace Forged
{

class LogService : public IService
{
public:

    enum class Level
    {
        Error = SPDLOG_LEVEL_ERROR,
        Warn = SPDLOG_LEVEL_WARN,
        Info = SPDLOG_LEVEL_INFO,
        Debug = SPDLOG_LEVEL_DEBUG
    };

    struct LogMessage
    {
        Level level;
        std::string payload;
    };

    LogService();

    template <typename... Args>
    using fmt = spdlog::format_string_t<Args...>;

    template<typename... Args>
    void error(fmt<Args...> fmt, Args&&... args)
    {
        mLogger->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(fmt<Args...> fmt, Args&&... args)
    {
        mLogger->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    // TODO Add other levels

    // TODO return subscription
    using MessageStreamHandler = std::function<void(const LogMessage)>;
    void subscribe(MessageStreamHandler handler);

    void onShutdown() override;

private:
    void createCustomLogger();

private:
    spdlog::pattern_formatter mFormatter;
    mutable std::shared_ptr<spdlog::logger> mLogger;
    rxcpp::subjects::subject<LogMessage> mStream;
};

}