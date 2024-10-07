cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(libimguizmo C CXX)

set(IMGUIZMO_SRC
  GraphEditor.cpp
  ImCurveEdit.cpp
  ImGradient.cpp
  ImGuizmo.cpp
  ImSequencer.cpp
)

add_library(imguizmo STATIC ${IMGUIZMO_SRC})

include_directories("../ImGui")

target_include_directories(imguizmo PUBLIC
  ${PROJECT_SOURCE_DIR}
)
