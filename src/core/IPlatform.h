#pragma once

#include <memory>
#include <string>
#include <core/ISystem.h>

namespace Engine
{

enum class GraphicsAPI 
{
    OpenGL,
    // Vulkan,
    // DirectX,
    // Metal,
};

class IPlatformData
{
public:
    virtual ~IPlatformData() noexcept = default;

    virtual GraphicsAPI getAPI() const = 0;
    virtual std::string getVersion() const = 0;
    virtual void* getWindowHandle() const = 0;
};

class IPlatform : public ISystem
{
public:
    using PlatformDataPtr = std::unique_ptr<IPlatformData>;

    virtual PlatformDataPtr getPlatformData() const = 0;
    virtual bool shouldClose() const = 0;
};

}