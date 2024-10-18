#pragma once

namespace Engine
{
    
class IService
{
public:
    virtual ~IService() noexcept = default;

    virtual void onShutdown() = 0;
};

}