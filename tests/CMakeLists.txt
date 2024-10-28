cmake_minimum_required(VERSION 3.3)

project(tests C CXX)

include_directories(
  ${SPDLOG_HEADERS}
  ${DI_HEADERS}
  ${GSL_HEADERS}
  ${BOOTS_HEADERS}
  ${RXCPP_HEADERS}
)

add_subdirectory(Catch2)

add_executable(tests
  test_store2.cpp
)

target_link_libraries(tests mylib Catch2WithMain)
set_target_properties(tests PROPERTIES OUTPUT_NAME "run-tests")
