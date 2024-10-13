cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(lib)

set(FRUIT_USES_BOOST OFF)

# Add third-party libraries
add_subdirectory(gl3w)
add_subdirectory(glfw)
add_subdirectory(ImGui)
add_subdirectory(ImGuizmo)
add_subdirectory(ImGuiNodeEditor)
add_subdirectory(implot)
add_subdirectory(squirrel)
add_subdirectory(fruit)

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
set(CATCH_HEADERS "${PROJECT_SOURCE_DIR}/catch" PARENT_SCOPE)
set(SQUIREL_HEADERS "${PROJECT_SOURCE_DIR}/squirrel/include" PARENT_SCOPE)
