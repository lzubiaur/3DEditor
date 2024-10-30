cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(APP_NAME "Forged")
set(APP_VERSION "1.0.0")
set(APP_RUNTIME_NAME "forged")

option(FORGED_USE_SCRIPT "Enable the scripting" OFF)

project(${APP_NAME} C CXX)
set(RUNTIME_NAME ${APP_RUNTIME_NAME})

message(STATUS "Building ${APP_NAME} ${APP_VERSION}...")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

# TODO GLFW compile options http://www.glfw.org/docs/latest/compile.html#compile_options_osx

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install/${CMAKE_BUILD_TYPE})

# Add custom cmake modules
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# DEBUG
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
# RELEASE
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Build options
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

# Compiler options
# set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") # Disable warnings

# Show all errors/warning on release build
# add_definitions(-Wall)

# Include the dependencies, tests and source
add_subdirectory(lib)
add_subdirectory(src)
# add_subdirectory(tests)
