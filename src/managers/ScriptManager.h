#pragma once

#ifdef FORGED_USE_SCRIPT 

#include <managers/IManager.h>
#include <string>
#include <squirrel.h>

namespace Forged
{

class ScriptManager : public IManager
{
public:
    ScriptManager();
    ~ScriptManager() = default;

    void onInitialize() override;
    void onShutdown() override;

    void onPreUpdate() override {}
    void onUpdate() override;
    void onPostUpdate() override {}

    bool run(const std::string& file);

private:
    void printSystemError(HSQUIRRELVM vm);

private:
    HSQUIRRELVM m_vm;
};

}

#endif
