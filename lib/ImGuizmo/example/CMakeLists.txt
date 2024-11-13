cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add sources
set(SOURCES
  main.cpp
  imgui_demo.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
  imgui.cpp
  imgui_draw.cpp
  ../ImSequencer.cpp
  ../GraphEditor.cpp
  ../ImGuizmo.cpp
  ../ImCurveEdit.cpp
)

# Add the executable
add_executable(my_executable ${SOURCES})

target_include_directories(my_executable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
