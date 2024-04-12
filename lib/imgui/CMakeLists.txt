cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(libimgui C CXX)

set(IMGUI_SRC
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
  backends/imgui_impl_opengl3.cpp
  backends/imgui_impl_glfw.cpp
)

include_directories("../glfw/include" "../gl3w/include")

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC
  ${PROJECT_SOURCE_DIR}
  "${PROJECT_SOURCE_DIR}/backends"
)
