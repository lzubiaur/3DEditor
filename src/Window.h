#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace Engine 
{

class Window 
{
public:
  Window(int width, int height);
  ~Window(); 

  bool init();

  const char* getGLSLVersion() const;
  GLFWwindow* getHandle();

protected:
  GLFWwindow *m_window;
  int width, height;
  std::string m_glslVersion;
  int m_glfwVersionMajor;
  int m_glfwVersionMinor;
};

}

#endif
