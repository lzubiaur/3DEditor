@echo off

if not exist lib\gl3w\src\gl3w.c (
  pushd lib\gl3w
  .\gl3w_gen.py
  popd
)

if not exist build\win (
  mkdir build\win
)

pushd build\win

set BUILD_TYPE=Debug

if /I "%1" == "debug" (
  set BUILD_TYPE=Debug
  echo "Build DEBUG"
)

cmake ^
    -G "Visual Studio 17 2022" ^
    -DBUILD_WIN=TRUE ^
    -DCMAKE_SYSTEM_VERSION=10.0 ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    ..\..

cmake --build . --target install --config %BUILD_TYPE%
 
popd
