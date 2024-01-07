cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project(rubik VERSION 0.1.0 LANGUAGES C CXX)
include(CTest)
enable_testing()
FILE(GLOB SOURCE_FILES src/*.cpp)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(lodepng CONFIG REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(triangle triangle.cpp)
add_executable(rect rect.cpp)
add_library(util ${SOURCE_FILES})
target_link_libraries(triangle PRIVATE util glfw glad::glad)
target_link_libraries(rect PRIVATE util glfw glad::glad)
target_link_libraries(util PRIVATE glfw GLEW::GLEW lodepng)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
