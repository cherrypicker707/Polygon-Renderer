cmake_minimum_required(VERSION 3.20)

project(polygon-renderer)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 23)
add_executable(polygon-renderer lib/src/glad.c src/main.c src/renderer.c src/polygon.c)
target_include_directories(polygon-renderer PUBLIC lib/inc)
target_link_libraries(polygon-renderer glfw GL X11 pthread Xrandr Xi dl)
