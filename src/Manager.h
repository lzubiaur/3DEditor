#pragma once

#include <ui/AppLog.h>
#include <Window.h>
#include <ui/AppLog.h>
#include <Script.h>
#include <IManager.h>

#include <spdlog/spdlog.h>

namespace Engine 
{

class Script;
class Window;

class Manager : public IManager
{
public:
  Manager();
  ~Manager();

  void startMainLoop();
  virtual std::shared_ptr<spdlog::logger> getLog() const override;

private:
  bool initialize();
  void shutdown();

  bool initializeUI();
  bool initializeScript();

  void shutDownUI();
  void shutDownScript();

  void createCustomLogger();

  std::unique_ptr<Window> m_window;
  Script m_script;
  bool m_showImGuiDemo;
  bool m_showImPlotDemo;
  
  AppLog m_appLog;
  bool m_appLogOpen = true;

  spdlog::pattern_formatter m_formatter;
  mutable std::shared_ptr<spdlog::logger> m_logger;
};

}
