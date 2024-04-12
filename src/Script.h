#pragma once

#include <IManager.h>
#include <string>
#include <squirrel.h>

namespace Engine
{

class Script
{
public:
    Script(IManager& manager);
    ~Script();

    bool initialize();
    void shutdown();

    bool run(const std::string& file);

private:
    void printSystemError(HSQUIRRELVM vm);

private:
    IManager& m_manager;
    HSQUIRRELVM m_vm;
};

}
