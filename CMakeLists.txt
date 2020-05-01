# Минимальная версия CMake.
cmake_minimum_required(VERSION 3.7.2)

# Проект.
project(Rubbur)

# Директория заголовочных файлов.
include_directories(include)
include_directories(include/RegExpr)
#include_directories(include/GUI)
#include_directories(include/CLI)
#include_directories(include/Utilities)

# Файлы исходного кода.
# set(SOURCES source/main.cpp) # - добавление вручную.
file(GLOB_RECURSE SOURCES "source/*.cpp") # - добавление из папки.
add_executable(Rubbur ${SOURCES})

# Флаги.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic -Wextra -fexceptions -O0 -g3 -ggdb -fsanitize=address --std=c++17")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic -Wextra -fexceptions -O0 -g3 -ggdb --std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 --std=c++17")

# Библиотеки.
target_link_libraries(Rubbur m)
#target_link_libraries(Rubbur pthread)
#target_link_libraries(Rubbur sfml-system)
#target_link_libraries(Rubbur sfml-graphics)
#target_link_libraries(Rubbur sfml-audio)
#target_link_libraries(Rubbur sfml-window)

