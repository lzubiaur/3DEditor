## Build on Windows

```bash
mkdir build
cd build
cmake -S .. -Wno-dev -G "Visual Studio 17 2022" -T ClangCL
cmake --build . 
```

## Git sub modules

Add submodule
``` bash
git submodule add <repository_url> <path/to/submodule>
git submodule update --init --recursive
git add .gitmodules submodule-folder
git commit -m "Added submodule"
```

Remove submodule
``` bash
vim .gitmodules
git rm --cached path/to/submodule
rm -rf path/to/submodule
vim .git/config
git add .gitmodules
git commit -m "Removed submodule"
```

## Third party dependencies

Installed dependencies

* catch: unit testing
* boost di - should be removed and use the boost distribution instead
* entt - entity component library
* fruit - DI from google
* gl3w - OpenGL core profile loading
* glfw - manage windows and OpenGL contexts
* GSL - Microsoft Guidelines Support Library
* ImGui
* ImGui Node Editor
* ImGuizmo
* ImPlot
* spdlog
* squirrel
* `boost 1.86.0` headers distribution must be installed manually


Following curated list of useful libraries that I’m considering or already installed.

### Serialization / Data Formats
- [https://github.com/protocolbuffers/protobuf](https://github.com/protocolbuffers/protobuf): Google's protocol buffers, a language-neutral, platform-neutral extensible mechanism for serializing structured data.
- [https://github.com/nlohmann/json](https://github.com/nlohmann/json): A JSON library for C++ providing easy manipulation of JSON data.
- [https://github.com/google/flatbuffers](https://github.com/google/flatbuffers): A memory-efficient serialization library developed by Google.

### Math / Graphics Libraries
- [https://github.com/google/mathfu](https://github.com/google/mathfu): A C++ math library focused on game development.
- [https://github.com/g-truc/glm](https://github.com/g-truc/glm): OpenGL Mathematics, a header-only C++ library for graphics software based on the GLSL specification.
- [https://github.com/Chlumsky/msdfgen](https://github.com/Chlumsky/msdfgen): A library for multi-channel signed distance field (SDF) generation for high-quality font rendering.
- [https://github.com/Reputeless/PerlinNoise](https://github.com/Reputeless/PerlinNoise): A C++ implementation of Perlin Noise, useful for procedural generation.
- [https://github.com/bulletphysics/bullet3](https://github.com/bulletphysics/bullet3): A physics simulation library used for collision detection, rigid body, and soft body dynamics.

### UI / Editor Libraries
- [https://github.com/Nelarius/imnodes](https://github.com/Nelarius/imnodes): A C++ library for node-based GUIs.
- [https://github.com/CedricGuillemet/ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo): Gizmo manipulation widgets for the Dear ImGui library.
- [https://github.com/thedmd/imgui-node-editor](https://github.com/thedmd/imgui-node-editor): A node editor built with Dear ImGui.
- [https://github.com/google/flatui](https://github.com/google/flatui): A library for creating flat, resolution-independent user interfaces.

### Entity-Component Systems (ECS)
- [https://github.com/alecthomas/entityx](https://github.com/alecthomas/entityx): A fast, type-safe C++ entity-component system.
- [https://github.com/skypjack/entt](https://github.com/skypjack/entt): A C++ entity-component system that focuses on performance and minimalism.

### Game Engines / Frameworks
- [https://github.com/bkaradzic/bgfx](https://github.com/bkaradzic/bgfx): A cross-platform rendering library.
- [https://github.com/SFML/SFML](https://github.com/SFML/SFML): Simple and Fast Multimedia Library for C++ that provides a windowing system, graphics, audio, and more.
- [https://github.com/crownengine/crown](https://github.com/crownengine/crown): A data-driven multi-platform game engine.
- [https://github.com/google/liquidfun](https://github.com/google/liquidfun): A physics engine for games focusing on 2D physics simulation.

### Scripting / Utilities
- [https://github.com/albertodemichelis/squirrel](https://github.com/albertodemichelis/squirrel): A high-level scripting language for embedding.
- [https://github.com/jarro2783/cxxopts](https://github.com/jarro2783/cxxopts): Lightweight C++ option parser.
- [https://github.com/bfgroup/Lyra](https://github.com/bfgroup/Lyra): A command-line argument parser for C++.
- [https://github.com/Tencent/rapidjson](https://github.com/Tencent/rapidjson): A fast JSON parser and generator for C++ with SAX/DOM-style API.
- [https://github.com/cacay/MemoryPool](https://github.com/cacay/MemoryPool): A C++ memory pool allocator for performance optimization.
- [https://github.com/catchorg/Catch2](https://github.com/catchorg/Catch2): A modern, C++-native, header-only test framework for unit tests.

### Networking / Messaging
- [https://github.com/zeromq/libzmq](https://github.com/zeromq/libzmq): The ZeroMQ messaging library, providing asynchronous messaging for scalable applications.
