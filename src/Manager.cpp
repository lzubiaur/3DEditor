#include <Manager.h>

#include <imgui.h>
// ImGui backend and renderer
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/callback_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <iostream>
#include <utility>
#include <memory>

#include <common.h>
#include <Editor/IUIControl.h>

namespace Engine
{

Manager::Manager()
: m_showImGuiDemo(true)
, m_showImPlotDemo(true)
, m_showImGuiDocking(true)
, m_script(*this)
{
  m_logger = std::make_shared<spdlog::logger>("default-multi-sink-logger");
  m_window = std::make_unique<Window>(640,480);
}

Manager::~Manager()
{
}

std::shared_ptr<spdlog::logger> Manager::getLog() const
{
  return m_logger;
}

void Manager::addControl(IUIControl *control)
{
  mControls.push_back(control);

  if (mRunning)
  {
    control->onInitialize();
  }
}

void Manager::startMainLoop() 
{
  if (!initialize())
  {
    return;
  }

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  mRunning = true;

  while (!glfwWindowShouldClose(m_window->getHandle())) 
  {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (m_showImGuiDemo)
    {
      ImGui::ShowDemoWindow(&m_showImGuiDemo);
    }

    if (m_showImGuiDocking)
    {
      // ImGui::ShowExampleAppDockSpace(&m_showImGuiDocking);
    }

    if (m_showImPlotDemo)
    {
      ImPlot::ShowDemoWindow(&m_showImPlotDemo);
    }

    m_appLog.draw("Log", &m_appLogOpen);

    for (IUIControl* control : mControls)
    {
      control->onDraw();
    }

    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(m_window->getHandle(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window->getHandle());
  }

  mRunning = false;

  shutdown();
}

bool Manager::initialize()
{
  if (!m_window->init()) 
  {
    return false;
  }

  createCustomLogger();

  return initializeUI() && initializeScript();
}

bool Manager::initializeScript()
{
  m_script.initialize();
  m_script.run("scripts/main.nut");

  return true;
}

bool Manager::initializeUI()
{
  bool succeeded = true;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImPlot::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  succeeded &= ImGui_ImplGlfw_InitForOpenGL(m_window->getHandle(), true);
  succeeded &= ImGui_ImplOpenGL3_Init(m_window->getGLSLVersion());

  for (IUIControl* control : mControls)
  {
    control->onInitialize();
  }

  return succeeded;
}

void Manager::createCustomLogger()
{
  auto callback_sink = std::make_shared<spdlog::sinks::callback_sink_mt>([&](const spdlog::details::log_msg &msg) 
  {
    spdlog::memory_buf_t formatted;
    m_formatter.format(msg, formatted);

    auto eol_len = strlen(spdlog::details::os::default_eol);
    std::string str(formatted.begin(), formatted.end() - eol_len);

    m_appLog.addLog(str.c_str());
  });

  // TODO add config to set the sinks and main levels
  callback_sink->set_level(spdlog::level::info);

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
  file_sink->set_level(spdlog::level::debug);

  m_logger->sinks().push_back(file_sink);
  m_logger->sinks().push_back(callback_sink);

  spdlog::set_level(spdlog::level::debug);
  spdlog::register_logger(m_logger);
  spdlog::set_default_logger(m_logger);
  // Loggers must be thread safe (_mt) when enabling the flush thread
  spdlog::flush_every(std::chrono::seconds(3));
  spdlog::flush_on(spdlog::level::err);
}

void Manager::shutdown()
{
  shutDownUI();
  shutDownScript();

  // TODO Move to Window class
  glfwDestroyWindow(m_window->getHandle());
  glfwTerminate();

  spdlog::shutdown();
}

void Manager::shutDownScript()
{
  m_script.shutdown(); 
}

void Manager::shutDownUI()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

}
