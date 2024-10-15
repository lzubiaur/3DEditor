#include <core/Platform.h>

#include <gsl/assert>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include <utils/Config.h>

namespace Engine
{

static void error_callback(int error, const char *description)
{
  std::cerr << "ERROR: " << description << " [" << error << "]" << std::endl;
}

Platform::Platform(int width, int height)
: mWidth(width)
, mHeight(height)
{
}

void Platform::onInitialize()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        return;
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    mGlslVersion = "#version 130";
    mGlfwVersionMajor = 3;
    mGlfwVersionMinor = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    std::stringstream windowTitle;
    windowTitle << Engine::AppName << " " << Engine::Version;

    // Create a windowed mode window and its OpenGL context
    mWindow = glfwCreateWindow(mWidth, mHeight, windowTitle.str().c_str(), NULL, NULL);
    Ensures(mWindow != nullptr);

    glfwMakeContextCurrent(mWindow);

    int initResult = gl3wInit();
    Ensures(initResult == GL3W_OK);

    Ensures(gl3wIsSupported(mGlfwVersionMajor, mGlfwVersionMinor));

    glfwSwapInterval(1); // Enable vsync
}

void Platform::onShutdown()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Platform::onPreUpdate()
{
    glfwPollEvents();

    int display_w, display_h;
    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLFWwindow* Platform::getWindowHandle() const
{
    return mWindow;
}

std::string Platform::getGLSLVersion() const
{
    return mGlslVersion;
}

IPlatform::PlatformDataPtr Platform::getPlatformData() const
{
    return std::make_unique<OpenGLAPIData>(*this);
}

bool Platform::shouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}

void Platform::onUpdate()
{}

void Platform::onPostUpdate()
{
    glfwSwapBuffers(mWindow);
}

OpenGLAPIData::OpenGLAPIData(const Platform& platform)
: mPlatform(platform)
{}

void* OpenGLAPIData::getWindowHandle() const
{
    return static_cast<void*>(mPlatform.getWindowHandle());
}

std::string OpenGLAPIData::getVersion() const
{
    return mPlatform.getGLSLVersion();
}

}
