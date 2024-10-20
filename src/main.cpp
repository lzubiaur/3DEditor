#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include <core/Application.h>
#include <core/Injectors.h>
#include <managers/UIManager.h>
#include <managers/ScriptManager.h>

#ifndef _WIN32
    #error "Only Windows platform build is supported at the moment"
#endif

#ifdef _WIN32
/* Faster builds with smaller header files */
#define VC_EXTRALEAN 1
#define WIN32_LEAN_AND_MEAN 1
/* TODO investigte the "NOapi" symbols */
/* (https://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx) */
#include <windows.h> /* WindMain */
#endif

#ifdef _WIN32
int CALLBACK WinMain(
    HINSTANCE hInstance,     /* handle to the current instance of the application. */
    HINSTANCE hPrevInstance, /* handle to the previous instance of the application */
    LPSTR lpCmdLine,         /* command line for the application */
    int nCmdShow)
{ /* controls how the window is to be shown */
#else
/* Linux and OSX use standard entry point */
int main(int argc, char *argv[])
{
#endif

    using namespace Forged;
    using Injector = Forged::Core::Injector;


    auto app = Injector::getApplicationInjector().create<std::unique_ptr<Application>>();

    app->addSystem(Injector::getManagerInjector(*app).create<std::shared_ptr<UIManager>>());
    app->addSystem(Injector::getManagerInjector(*app).create<std::shared_ptr<ScriptManager>>());

    app->run();

    return EXIT_SUCCESS;
}
