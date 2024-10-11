#pragma once

#include <ui/AppLog.h>
#include <Window.h>
#include <ui/AppLog.h>
#include <Script.h>
#include <IManager.h>
#include <Editor/MainWindow.h>

#include <spdlog/spdlog.h>

namespace Engine 
{

class IUIControl;
class Script;
class Window;

// TODO rename Application

class Manager : public IManager
{
public:
  Manager();
  ~Manager();

  void startMainLoop();
  virtual std::shared_ptr<spdlog::logger> getLog() const override;

  virtual void addControl(IUIControl *control) override;

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

  std::unique_ptr<Window> m_window;
  Script m_script;
  bool m_showImGuiDemo;
  bool m_showImPlotDemo;
  bool m_showImGuiDocking;
  
  AppLog m_appLog;
  bool m_appLogOpen = true;

  std::vector<IUIControl*> mControls;

  spdlog::pattern_formatter m_formatter;
  mutable std::shared_ptr<spdlog::logger> m_logger;
};

}
