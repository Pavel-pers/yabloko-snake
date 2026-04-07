cmake_minimum_required(VERSION 3.20)
project(yabloko C CXX ASM)

set(CMAKE_C_FLAGS "-m32 -ffreestanding -I${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE ALL_SOURCES
        "*.c" "*.cpp" "*.h" "*.S"
)

add_executable(fake_target ${ALL_SOURCES}
        user/snake_inputs.cpp
        user/snake_render.cpp
        drivers/speaker.c
        drivers/speaker.h
        user/snake_sounds.cpp
        user/snake_map.cpp
        user/snake_snake.cpp
        user/snake_snake.h
        user/snake_map.h
        user/snake_gameplay.cpp
        user/snake_gameplay.h
        user/snake_map.cpp
        user/snake_render.h
        user/snake_random.cpp
        user/snake_random.h
        user/snake_inputs.h
        user/snake_sounds.h
        user/snake_menu.cpp
        user/snake_menu.h
        user/snake_main.cpp)