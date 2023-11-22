cmake_minimum_required(VERSION 3.24)
project(source)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
add_executable(main.cpp main.cpp
        Person.hpp)
target_link_libraries(main.cpp PRIVATE fmt::fmt)


add_subdirectory(basics)
add_subdirectory(generic)
add_subdirectory(lib)
add_subdirectory(poly)
