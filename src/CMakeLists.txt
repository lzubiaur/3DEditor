cmake_minimum_required(VERSION 3.5)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_BINARY_DIR}/src
  ${GLFW_HEADERS}
  ${SPDLOG_HEADERS}
  ${SQUIREL_HEADERS}
  ${IMGUI_NODE_EDITOR}
  ${DI_HEADERS}
  ${GSL_HEADERS}
  ${BOOTS_HEADERS}
)

add_library(engine STATIC 
  core/Platform.cpp 
  core/Application.cpp
  managers/UIManager.cpp
  managers/ScriptManager.cpp
  editor/UIRenderer.cpp 
  editor/MessageConsole.cpp
  editor/MainWindow.cpp
  editor/NodeGraph.cpp
  editor/UserControl.cpp
  editor/MainMenu.cpp
  services/LogService.cpp
)

target_link_libraries(engine
  gl3w
  glfw
  imgui
  implot
  imguinodeeditor
  imguizmo
  sqstdlib_static
  squirrel_static
  ${GLFW_LIBRARIES}
)

target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Runtime executable
add_executable(rt main.cpp)

# Linking against static GLFW libary. GLFW_LIBRARIES must be used to add
# dependencies (http://www.glfw.org/docs/latest/build.html).
target_link_libraries(rt engine)
set_target_properties(rt PROPERTIES OUTPUT_NAME ${RUNTIME_NAME})

if (WIN32)
    set_target_properties(rt PROPERTIES WIN32_EXECUTABLE true)
endif()

set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")

install(TARGETS rt RUNTIME DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/scripts DESTINATION ${INSTALL_DIR})