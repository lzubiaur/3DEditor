#pragma once

namespace Forged
{
    
class IService
{
public:
    virtual ~IService() noexcept = default;

    virtual void onShutdown() = 0;
};

}