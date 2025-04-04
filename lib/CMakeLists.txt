cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(lib)

# Boost 1_86_0 must be installed manually (copy headers only)

# GLFW 
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

# Squirrel
set(SQ_DISABLE_INTERPRETER ON)

# Add third-party libraries
add_subdirectory(gl3w)
add_subdirectory(glfw)
add_subdirectory(ImGui)
add_subdirectory(ImGuizmo)
add_subdirectory(ImGuiNodeEditor)
add_subdirectory(implot)
if(FORGED_USE_SCRIPT)
    add_subdirectory(squirrel)
endif()

# set(FRUIT_USES_BOOST OFF)
# add_subdirectory(fruit)

# HACK force the gl3w files generation
message(CHECK_START "Generating gl3w sources")
execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
    ${PROJECT_SOURCE_DIR}/gl3w/gl3w_gen.py --root ${PROJECT_BINARY_DIR}/gl3w
    RESULT_VARIABLE gl3w_result
)

set(IMGUI_NODE_EDITOR "${PROJECT_SOURCE_DIR}/ImGuiNodeEditor" PARENT_SCOPE)
set(SPDLOG_HEADERS "${PROJECT_SOURCE_DIR}/spdlog/include" PARENT_SCOPE)
set(GLFW_HEADERS "${PROJECT_SOURCE_DIR}/glfw/include" PARENT_SCOPE)
set(DI_HEADERS "${PROJECT_SOURCE_DIR}/DI/include" PARENT_SCOPE)
set(GSL_HEADERS "${PROJECT_SOURCE_DIR}/GSL/include" PARENT_SCOPE)
set(BOOTS_HEADERS "${PROJECT_SOURCE_DIR}/boost_1_86_0" PARENT_SCOPE)
set(RXCPP_HEADERS "${PROJECT_SOURCE_DIR}/RxCpp/Rx/v2/src" PARENT_SCOPE)
if(FORGED_USE_SCRIPT)
    set(SQUIREL_HEADERS "${PROJECT_SOURCE_DIR}/squirrel/include" PARENT_SCOPE)
endif()