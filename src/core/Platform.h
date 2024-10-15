#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include <core/IPlatform.h>
#include <core/IApplication.h>

namespace Engine 
{

class Platform : public IPlatform
{
public:
    Platform();
    ~Platform() = default;

    Platform(Platform&&) noexcept = delete;
    Platform& operator=(Platform&&) noexcept = delete;

    Platform(Platform&) noexcept = delete;
    Platform& operator=(Platform&) noexcept = delete;

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override;
    void onUpdate() override;
    void onPostUpdate() override;

    PlatformDataPtr getPlatformData() const override;
    bool shouldClose() const override;

    GLFWwindow* getWindowHandle() const;
    std::string getGLSLVersion() const;

protected:
    GLFWwindow* mWindow;
    int mWidth, mHeight;
    std::string mGlslVersion;
    int mGlfwVersionMajor;
    int mGlfwVersionMinor;
};

class OpenGLAPIData : public IPlatformData
{
public:
    OpenGLAPIData() = delete;
    OpenGLAPIData(const Platform& platform);

    GraphicsAPI getAPI() const override { return GraphicsAPI::OpenGL; }
    std::string getVersion() const override;
    void* getWindowHandle() const override;

private:
    const Platform& mPlatform;
};

}