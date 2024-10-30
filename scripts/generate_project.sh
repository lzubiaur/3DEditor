BUILD_DIR="$(pwd)/build"

mkdir -p "$BUILD_DIR"

pushd $BUILD_DIR

cmake -S .. -B "$BUILD_DIR" \
      -G "Visual Studio 17 2022" \
      -T ClangCL \
      -Wno-dev

popd