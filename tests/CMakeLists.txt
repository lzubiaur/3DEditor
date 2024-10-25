cmake_minimum_required(VERSION 3.3)

project(tests C CXX)

include_directories(
  ${CATCH_HEADERS}
  ${SPDLOG_HEADERS}
  ${DI_HEADERS}
  ${GSL_HEADERS}
  ${BOOTS_HEADERS}
  ${RXCPP_HEADERS}
)

add_executable(tests
  main.cpp
  test_store.cpp
)

target_link_libraries(tests mylib)
set_target_properties(tests PROPERTIES OUTPUT_NAME "run-tests")
