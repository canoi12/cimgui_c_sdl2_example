cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cimgui_sdl2 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)
include_directories(include/cimgui)
include_directories(include/cimgui/imgui)
include_directories(include/imgui_impl)

add_subdirectory(include/cimgui)

add_library(imgui_impl_opengl3 STATIC include/imgui_impl/imgui_impl_opengl3.cpp)
add_library(imgui_impl_sdl STATIC include/imgui_impl/imgui_impl_sdl.cpp)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W)
target_compile_definitions(imgui_impl_sdl PRIVATE IMGUI_IMPL_API=extern\ \"C\")
target_compile_definitions(imgui_impl_opengl3 PRIVATE IMGUI_IMPL_API=extern\ \"C\")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cimgui_sdl2 main.c include/GL/gl3w.c)

target_compile_definitions(cimgui_sdl2 PRIVATE IMGUI_IMPL_API=)
target_link_libraries(cimgui_sdl2 ${SDL2_LIBRARIES})
target_link_libraries(cimgui_sdl2 GL m dl cimgui imgui_impl_opengl3 imgui_impl_sdl)