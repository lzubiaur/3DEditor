#ifdef FORGED_USE_SCRIPT 

#include <managers/ScriptManager.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>

#include <wchar.h>
#include <wctype.h>

// #include <ui/AppLog.h>
#include <spdlog/spdlog.h>

namespace Forged
{

std::string toChar(const SQChar* wstr)
{
#ifdef _UNICODE
    static char str[256] = {0};
    std::wcstombs(str, wstr, 255);

    return std::string(str);
#else
    return wstr;
#endif
}

void ScriptManager::onUpdate()
{

}

IManager* getManager(HSQUIRRELVM SQ_UNUSED_ARG(m_vm))
{
    SQUserPointer ud = nullptr;

    sq_pushroottable(m_vm);
    sq_pushstring(m_vm, _SC("_manager"), -1);

    if (SQ_SUCCEEDED(sq_get(m_vm, -2))) 
    {
        sq_getuserpointer(m_vm, -1, &ud);
    }

    sq_pop(m_vm, 2);
    
    return static_cast<IManager*>(ud);
}

void printFunc(HSQUIRRELVM SQ_UNUSED_ARG(m_vm), const SQChar *s, ...)
{
    IManager* manager = getManager(m_vm);
    std::string str = toChar(s);

    va_list vl;
    static char buf[4096];

    va_start(vl, s);
    vsprintf(&buf[0], str.c_str(), vl);
    va_end(vl);

    // TODO notify the UI to write the message
    // manager->getLog()->info(buf, vl);
}

ScriptManager::ScriptManager()
{}

void ScriptManager::onInitialize()
{
    m_vm = sq_open(1024);

	sqstd_seterrorhandlers(m_vm); // registers the default error handlers

	sq_pushroottable(m_vm); // push the root table(were the globals of the ScriptManager will be stored)

    // Initialize standard libraries
    if(!SQ_SUCCEEDED(sqstd_register_iolib(m_vm)))
    {
        printSystemError(m_vm);

        return;
    }
    // sqstd_register_bloblib(m_vm);
    // sqstd_register_stringlib(m_vm);
    // sqstd_register_mathlib(m_vm);
    // sqstd_register_systemlib(m_vm);

    // set the output and error print functions
    sq_setprintfunc(m_vm, printFunc, printFunc);
 
    // push the manager reference into the root table

    // TODO
    // sq_pushstring(m_vm, _SC("_manager"), -1);
    // sq_pushuserpointer(m_vm, &m_manager);
    // if (!SQ_SUCCEEDED(sq_newslot(m_vm, -3, false)))
    // {
    //     printSystemError(m_vm);
    // }
}

void ScriptManager::onShutdown()
{
	sq_pop(m_vm, 1); // pops the root table
    sq_close(m_vm); // closes the virtual machine
}

bool ScriptManager::run(const std::string& file)
{
    // TODO
    // m_manager.getLog()->info("Running ScriptManager {}...\n", file.c_str());
	
    // Load and execute the main ScriptManager
    if (SQ_FAILED(sqstd_dofile(m_vm, file.c_str(), false, true))) 
    {
        printf("Failed to load ScriptManager!\n");
        printSystemError(m_vm);

        return false;
    }

    return true;
}

void ScriptManager::printSystemError(HSQUIRRELVM m_vm) 
{
    const SQChar* errorString;

    if (sq_gettop(m_vm) >= 1) 
    {
        if (SQ_SUCCEEDED(sq_getstring(m_vm, 2, &errorString))) 
        {
            printf("Error: %s\n", errorString);
            return;
        }
    }

    printf("Unknown error\n");
}

}

#endif