#include <stdio.h>
#include <stdlib.h>

#include <Application.h>
#include <common.h>
#include <Editor/NodeGraph.h>

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
  LPSTR     lpCmdLine,     /* command line for the application */
  int       nCmdShow) {    /* controls how the window is to be shown */
#else
/* Linux and OSX use standard entry point */
int main(int argc, char *argv[]) {
#endif

  Engine::Application app;

  Engine::NodeGraph node;
  app.addControl(&node);

  app.startMainLoop();

  return EXIT_SUCCESS;
}
