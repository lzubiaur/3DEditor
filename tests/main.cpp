// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <spdlog/spdlog.h>

#include <iostream>

int main(int argc, char *argv[]) 
{
  // spdlog::stdout_color_mt("console");
  spdlog::set_level(spdlog::level::debug);

  int rc = Catch::Session().run(argc, argv);

  return rc;
}
