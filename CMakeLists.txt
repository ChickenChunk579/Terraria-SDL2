cmake_minimum_required(VERSION 3.2)

project(terraria)

set(SDL2IMAGE_INSTALL OFF)
set(SDL2TTF_INSTALL OFF)
set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_OPUS OFF)
set(SDL2MIXER_MOD OFF)
set(SDL2MIXER_MIDI OFF)
set(SDL2MIXER_WAVPACK OFF)

set(SDL2IMAGE_SAMPLES OFF)

set(BUILD_SHARED_LIBS FALSE)

set(YAML_BUILD_SHARED_LIBS OFF)

add_executable(client
    client/main.cpp
)

if (CMAKE_SYSTEM_NAME MATCHES Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_library(ImGui STATIC
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui.cpp
    vendor/imgui/backends/imgui_impl_sdl2.cpp
    vendor/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

add_library(wldlib STATIC
    vendor/wldlib/src/log.c
    vendor/wldlib/src/parseutil.c
    vendor/wldlib/src/rand.c
    vendor/wldlib/src/tilefuncs.c
    vendor/wldlib/src/wldfuncs.c
    vendor/wldlib/src/wldheaderfuncs.c
    vendor/wldlib/src/wldlib.c
    vendor/wldlib/src/worldgen.c

    vendor/wldlib/src/filestream.h
    vendor/wldlib/src/log.h
    vendor/wldlib/src/parseutil.h
    vendor/wldlib/src/rand.h
    vendor/wldlib/src/tile.h
    vendor/wldlib/src/tilefuncs.h
    vendor/wldlib/src/types.h
    vendor/wldlib/src/wld.h
    vendor/wldlib/src/wldfuncs.h
    vendor/wldlib/src/wldheader.h
    vendor/wldlib/src/wldheaderfuncs.h
    vendor/wldlib/src/wldlib.h
    vendor/wldlib/src/worldgen.h
)


add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_ttf)
add_subdirectory(vendor/SDL_mixer)
add_subdirectory(vendor/yaml-cpp)

if (CMAKE_SYSTEM_NAME MATCHES Emscripten)
    target_include_directories(SDL2_ttf PRIVATE vendor/SDL_ttf/external/freetype/include)

    target_link_options(client PRIVATE -sASSERTIONS -sALLOW_MEMORY_GROWTH --preload-file Content/ -sMEMORY64=1)
    target_link_options(ImGui PRIVATE -sASSERTIONS -sALLOW_MEMORY_GROWTH -sMEMORY64=1)
    target_link_options(wldlib PRIVATE -sASSERTIONS -sALLOW_MEMORY_GROWTH -sMEMORY64=1)
    target_compile_options(client PRIVATE -sMEMORY64=1)
    target_compile_options(ImGui PRIVATE -sMEMORY64=1)
    target_compile_options(wldlib PRIVATE -sMEMORY64=1)
    target_compile_options(spdlog PRIVATE -sMEMORY64=1)
    target_compile_options(SDL2_ttf PRIVATE -sMEMORY64=1)
    target_compile_options(SDL2_mixer PRIVATE -sMEMORY64=1)
    target_compile_options(SDL2_image PRIVATE -sMEMORY64=1)
    target_compile_options(SDL2-static PRIVATE -sMEMORY64=1)
    target_compile_options(freetype PRIVATE -sMEMORY64=1)
endif()

target_include_directories(ImGui PRIVATE vendor/imgui vendor/imgui/backends)
target_link_libraries(ImGui PRIVATE)

target_include_directories(client PRIVATE client common  vendor/imgui vendor/imgui/backends vendor/wldlib/src spdlog)

target_link_libraries(client PRIVATE ImGui spdlog wldlib)

target_link_libraries(ImGui PRIVATE SDL2-static)
target_include_directories(ImGui PRIVATE vendor/SDL/include)

target_link_libraries(client PRIVATE SDL2-static SDL2_image SDL2_ttf SDL2_mixer yaml-cpp)
target_include_directories(client PRIVATE vendor/SDL/include vendor/SDL_image vendor/SDL_ttf vendor/SDL_mixer/include yaml-cpp)