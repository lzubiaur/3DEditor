#include <services/LogService.h>

#include <spdlog/sinks/callback_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Engine
{

LogService::LogService()
{
  mLogger = std::make_shared<spdlog::logger>("default-multi-sink-logger");
}

void LogService::createCustomLogger()
{
  auto callback_sink = std::make_shared<spdlog::sinks::callback_sink_mt>([&](const spdlog::details::log_msg &msg) 
  {
    spdlog::memory_buf_t formatted;
    mFormatter.format(msg, formatted);

    auto eol_len = strlen(spdlog::details::os::default_eol);
    std::string str(formatted.begin(), formatted.end() - eol_len);

    // TODO
    // mAppLog.addLog(str.c_str());
  });

  // TODO add config to set the sinks and main levels
  callback_sink->set_level(spdlog::level::info);

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
  file_sink->set_level(spdlog::level::debug);

  mLogger->sinks().push_back(file_sink);
  mLogger->sinks().push_back(callback_sink);

  spdlog::set_level(spdlog::level::debug);
  spdlog::register_logger(mLogger);
  spdlog::set_default_logger(mLogger);
  // Loggers must be thread safe (_mt) when enabling the flush thread
  spdlog::flush_every(std::chrono::seconds(3));
  spdlog::flush_on(spdlog::level::err);
}

void LogService::onShutdown()
{
  spdlog::shutdown();
}

}