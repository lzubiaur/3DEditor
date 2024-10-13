#pragma once

#include <managers/IManager.h>
#include <string>
#include <squirrel.h>

namespace Engine
{

class ScriptManager : IManager
{
public:
    ScriptManager(IManager& manager);
    ~ScriptManager();

    void onInitialize() override;
    void onUpdate() override;
    void onShutdown() override;

    bool run(const std::string& file);

private:
    void printSystemError(HSQUIRRELVM vm);

private:
    IManager& m_manager;
    HSQUIRRELVM m_vm;
};

}
