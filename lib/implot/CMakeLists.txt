cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(libimplot C CXX)

set(IMPLOT_SRC
  implot.cpp
  implot_demo.cpp
  implot_items.cpp
)

include_directories("../imgui")

add_library(implot STATIC ${IMPLOT_SRC})

target_include_directories(implot PUBLIC
  ${PROJECT_SOURCE_DIR}
)
