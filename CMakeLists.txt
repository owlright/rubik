cmake_minimum_required(VERSION 3.15.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_Release ${CMAKE_CURRENT_SOURCE_DIR}/Release)
project(rubik VERSION 0.1.0 LANGUAGES C CXX)
# ! 方便调试
set(CMAKE_VERBOSE_MAKEFILE ON)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("/utf-8")
     # ! 设置 Debug 模式下使用静态链接的运行时库
    #  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    # 设置使用静态链接的多线程运行时库（调试版本）只有在cmake version >= 3.15时才支持
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(lodepng CONFIG REQUIRED)


add_subdirectory(src)
include(cmake/Util.cmake)
subdirlist(examples ${CMAKE_CURRENT_SOURCE_DIR}/examples)
message(STATUS "examples: ${examples}")
add_subdirectory(examples)
add_subdirectory(exercise)