#pragma once

#include <ui/AppLog.h>
#include <Platform.h>
#include <ui/AppLog.h>
#include <Script.h>
#include <IManager.h>
#include <Editor/MainWindow.h>

#include <spdlog/spdlog.h>

namespace Engine 
{

class IUIControl;
class Script;
class Platform;

class Application : public IManager
{
public:
  Application();
  ~Application();

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

  std::unique_ptr<Platform> mPlatform;
  Script mScript;
  bool mShowImGuiDemo;
  bool mShowImPlotDemo;
  bool mShowImGuiDocking;
  
  AppLog mAppLog;
  bool mAppLogOpen = true;

  std::vector<IUIControl*> mControls;

  spdlog::pattern_formatter mFormatter;
  mutable std::shared_ptr<spdlog::logger> mLogger;
};

}
