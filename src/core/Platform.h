#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace Engine 
{

class Platform 
{
public:
    Platform(int width, int height);
    ~Platform() = default;

    Platform(Platform&&) noexcept = delete;
    Platform& operator=(Platform&&) noexcept = delete;

    Platform(Platform&) noexcept = delete;
    Platform& operator=(Platform&) noexcept = delete;

    bool initialize();
    void shutdown();

    const char *getGLSLVersion() const;
    GLFWwindow *getHandle();

protected:
    GLFWwindow *mWindow;
    int width, height;
    std::string mGlslVersion;
    int mGlfwVersionMajor;
    int mGlfwVersionMinor;
};

}