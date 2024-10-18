#pragma once

#include <services/IService.h>
#include <spdlog/spdlog.h>

namespace Engine
{

class LogService : public IService
{
public:
    LogService();

    // TODO hide logger implementation in a wrapper class
    virtual std::shared_ptr<spdlog::logger> getLog() const { return mLogger; }

    void onShutdown() override;

private:
    void createCustomLogger();

private:
    spdlog::pattern_formatter mFormatter;
    mutable std::shared_ptr<spdlog::logger> mLogger;
};

}