cmake_minimum_required(VERSION 3.5)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_BINARY_DIR}/src
  ${GLFW_HEADERS}
  ${SPDLOG_HEADERS}
  ${IMGUI_NODE_EDITOR}
  ${DI_HEADERS}
  ${GSL_HEADERS}
  ${BOOTS_HEADERS}
  ${RXCPP_HEADERS}
)

add_library(mylib STATIC 
  core/Platform.cpp 
  core/Application.cpp
  managers/UIManager.cpp
  managers/ScriptManager.cpp
  view/ImGui/UIRenderer.cpp 
  view/ImGui/MessagePanel.cpp
  view/ImGui/MainWindow.cpp
  view/ImGui/NodeGraph.cpp
  view/ImGui/MainMenu.cpp
  view/ImGui/UIBuilder.cpp
  presenter/PresenterBase.cpp
  presenter/MainMenu.cpp
  presenter/DemoPanel.cpp
  presenter/PlotDemoPanel.cpp
  presenter/MessagePanel.cpp
  services/LogService.cpp
  services/EventLoop.cpp
  state/Reducers.cpp
)

target_link_libraries(mylib
  gl3w
  glfw
  imgui
  implot
  imguinodeeditor
  imguizmo
  ${GLFW_LIBRARIES}
)

if(FORGED_USE_SCRIPT)
  include_directories(${SQUIREL_HEADERS})
  target_link_libraries(mylib sqstdlib_static squirrel_static)
  target_compile_definitions(my_executable PRIVATE FORGED_USE_SCRIPT)
endif()

target_include_directories(mylib PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Runtime executable
add_executable(myruntime main.cpp)

target_compile_definitions(mylib PRIVATE
    APP_NAME="${APP_NAME}"
    APP_VERSION="${APP_VERSION}"
)

# Linking against static GLFW libary. GLFW_LIBRARIES must be used to add
# dependencies (http://www.glfw.org/docs/latest/build.html).
target_link_libraries(myruntime mylib)
set_target_properties(myruntime PROPERTIES OUTPUT_NAME ${RUNTIME_NAME})

if (WIN32)
    set_target_properties(myruntime PROPERTIES WIN32_EXECUTABLE true)
endif()

set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")

install(TARGETS myruntime RUNTIME DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/scripts DESTINATION ${INSTALL_DIR})