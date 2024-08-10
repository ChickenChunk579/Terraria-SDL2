# Terraria SDL2
## A remake of Terraria using C++, SDL2, ImGui and Nuklear

# Compiling

1. Clone the repository

`git clone https://github.com/ChickenChunk579/Terraria-SDL2`

2. Update submodules

`git submodule update --init --recursive`

3. Configure the project with CMake

`
cd build/{platform}
cmake ../.. -G{build system, like Ninja}
`

4. Compile the project using your build system of choice
e.g:

`ninja`

# Compiling on Web

1. Complete steps 1 and 2 from the normal compilation guide

2. Install Emscripten SDK

3. Configure the project with emcmake

`
cd build/wasm
emcmake cmake .. -GNinja
`

4. Open the client.html file in a browser with a webserver.

NOTE: Currently required Memory64 flag to be enabled.