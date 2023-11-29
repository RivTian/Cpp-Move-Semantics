cmake_minimum_required(VERSION 3.26)
project(generic)

file(GLOB SOURCE_FILES *.c *.cpp)
find_package(fmt CONFIG REQUIRED)

foreach(SOURCE_PATH ${SOURCE_FILES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt)
endforeach(SOURCE_PATH ${SOURCE_FILES})