cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(libimguinodeeditor C CXX)

set(IMGUI_NODE_EDITOR_SRC
  crude_json.cpp
  imgui_canvas.cpp
  imgui_node_editor.cpp
  imgui_node_editor_api.cpp
)

include_directories("../ImGui")

add_library(imguinodeeditor STATIC ${IMGUI_NODE_EDITOR_SRC})

target_include_directories(imguinodeeditor PUBLIC
  ${PROJECT_SOURCE_DIR}
)
