#include <stdio.h>
#include <stdlib.h>

#include <core/IApplication.h>
#include <core/Injectors.h>

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

    using namespace Engine;

    // TODO use reference instead of unique pointer
    auto app = getApplicationInjector().create<std::unique_ptr<Application>>();

    auto uiManager = getManagerInjector(*app).create<UIManager>();
    app->addSystem(uiManager);

    app->run();

    // auto platform = std::make_unique<Platform>(600, 600);
    // std::vector<std::unique_ptr<IManager>> managers;
    // managers.push_back(std::make_unique<ScriptManager>());
    // managers.push_back(std::make_unique<UIManager>());

    // Application app(std::move(platform), managers);
    // app.run();
    
    return EXIT_SUCCESS;
}
