cmake_minimum_required(VERSION 3.20)
project(vimacs)

set(CMAKE_CXX_STANDARD 14)

include_directories(include ~/.brew/Cellar/libgit2/1.4.3/include/)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(include)

add_executable(vimacs
        srcs/main.cpp
        srcs/Terminal.cpp
        include/Vimacs.hpp srcs/Terminal.cpp)

target_link_libraries(vimacs ${CURSES_LIBRARIES} -L/Users/hsabir/.brew/Cellar/libgit2/1.4.3/lib -lgit2)