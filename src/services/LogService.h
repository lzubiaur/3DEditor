#pragma once

#include <services/IService.h>
#include <spdlog/spdlog.h>

namespace Engine
{

class LogService : public IService
{
public:
    LogService();
    virtual std::shared_ptr<spdlog::logger> getLog() const;

private:
    void createCustomLogger();

private:
  spdlog::pattern_formatter mFormatter;
  mutable std::shared_ptr<spdlog::logger> mLogger;
};

}