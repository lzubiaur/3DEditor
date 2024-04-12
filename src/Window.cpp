#include "Window.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include <Config.h>

namespace Engine {

  static void error_callback(int error, const char* description) {
    std::cerr << "ERROR: " << description << " [" << error << "]" << std::endl;
  }

  Window::Window(int width, int height) : width(width), height(height)
  {}

  Window::~Window()
  {}

  bool Window::init()
  {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) 
    {
      return false;
    }

#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    m_glslVersion = "#version 100";
    m_glfwVersionMajor = 2;
    m_glfwVersionMinor = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    m_glslVersion = "#version 150";
    m_glfwVersionMajor = 3;
    m_glfwVersionMinor = 2;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    m_glslVersion  = "#version 130";
    m_glfwVersionMajor = 3;
    m_glfwVersionMinor = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    std::stringstream windowTitle;
    windowTitle << Engine::AppName << " " << Engine::Version;

    // Create a windowed mode window and its OpenGL context
    m_window = glfwCreateWindow(width, height, windowTitle.str().c_str(), NULL, NULL);

    if (!m_window) 
    {
      glfwTerminate();

      return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    if (gl3wInit())
    {
      // LOG_ERROR("Failed to initialize OpenGL");

      return false;
    }

    if (!gl3wIsSupported(m_glfwVersionMajor, m_glfwVersionMinor))
    {
      // LOG_ERROR("OpenGL {}.{} not supported", m_glfwVersionMajor, m_glfwVersionMinor);

      return false;
    }

    glfwSwapInterval(1); // Enable vsync

    // TODO
    // LOG_DEBUG("Running OpenGL {} GLSL {}", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    return true;
  }

const char* Window::getGLSLVersion() const
{
  return m_glslVersion.c_str();
}

  GLFWwindow* Window::getHandle()
  {
    return m_window;
  }


}
