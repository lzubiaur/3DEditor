#include <core/Application.h>

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

#include <core/Common.h>

namespace Engine
{

Application::Application()
{
  mLogger = std::make_shared<spdlog::logger>("default-multi-sink-logger");

  // TODO Use DI
  mPlatform = std::make_unique<Platform>(640,480);
}

Application::~Application()
{
}

std::shared_ptr<spdlog::logger> Application::getLog() const
{
  return mLogger;
}

void Application::run() 
{
  if (!initialize())
  {
    return;
  }

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  mRunning = true;

  while (!glfwWindowShouldClose(mPlatform->getHandle())) 
  {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO draw controls

    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(mPlatform->getHandle(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(mPlatform->getHandle());
  }

  mRunning = false;

  shutdown();
}

bool Application::initialize()
{
  if (!mPlatform->init()) 
  {
    return false;
  }

  createCustomLogger();

  return initializeUI() && initializeScript();
}

bool Application::initializeScript()
{
  // TODO initialize managers
  // mScript.initialize();
  // mScript.run("scripts/main.nut");

  return true;
}

bool Application::initializeUI()
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

  succeeded &= ImGui_ImplGlfw_InitForOpenGL(mPlatform->getHandle(), true);
  succeeded &= ImGui_ImplOpenGL3_Init(mPlatform->getGLSLVersion());

  // TODO initialize managers

  return succeeded;
}

void Application::createCustomLogger()
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

void Application::shutdown()
{
  shutDownUI();
  shutDownScript();

  // TODO Move to Platform class
  glfwDestroyWindow(mPlatform->getHandle());
  glfwTerminate();

  // TODO shutdowns managers

  spdlog::shutdown();
}

void Application::shutDownScript()
{
  // mScript.shutdown(); 
}

void Application::shutDownUI()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

}
