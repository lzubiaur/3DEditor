#pragma once

#include <core/Platform.h>
#include <spdlog/spdlog.h>

namespace Engine 
{

class IUIControl;
class Script;
class Platform;

class Application
{
public:
  Application();
  ~Application();

  void run();

  // TODO create a looger service
  virtual std::shared_ptr<spdlog::logger> getLog() const;

private:
  bool initialize();
  void shutdown();

  bool initializeUI();
  bool initializeScript();

  void shutDownUI();
  void shutDownScript();

  void createCustomLogger();

public:

  bool mRunning = false;

  std::unique_ptr<Platform> mPlatform;
  bool mAppLogOpen = true;

  spdlog::pattern_formatter mFormatter;
  mutable std::shared_ptr<spdlog::logger> mLogger;
};

}
