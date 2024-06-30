cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#   CACHE STRING "Vcpkg toolchain file")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_Release ${CMAKE_CURRENT_SOURCE_DIR}/Release)
project(rubik VERSION 0.1.0 LANGUAGES C CXX)
# include(CTest)
# enable_testing()
FILE(GLOB SOURCE_FILES src/*.cpp)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(lodepng CONFIG REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/exercise)
# Get a list of all .cpp files
file(GLOB EXERCISE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/exercise/*.cpp")
foreach(CPP_FILE ${EXERCISE_FILES})
    # Get the filename without directory or extension
    get_filename_component(CPP_FILE_WE ${CPP_FILE} NAME_WE)
    # Add compile target
    add_executable(${CPP_FILE_WE} ${CPP_FILE})
    # Link to the library
    target_link_libraries(${CPP_FILE_WE} PRIVATE util glfw glad::glad)
endforeach()

add_executable(triangle triangle.cpp)
add_executable(rect rect.cpp)
add_executable(line drawLine.cpp)
add_executable(quad drawQuad.cpp)
add_executable(texture imageTexture.cpp)
add_library(util ${SOURCE_FILES})
target_link_libraries(triangle PRIVATE util glfw glad::glad)
target_link_libraries(rect PRIVATE util glfw glad::glad)
target_link_libraries(util PRIVATE glfw lodepng)
target_link_libraries(line PRIVATE util glfw glad::glad)
target_link_libraries(quad PRIVATE util glfw glad::glad)
target_link_libraries(texture PRIVATE util glfw glad::glad)
# 仅当使用MSVC编译器时设置/SUBSYSTEM:WINDOWS
if(MSVC)
    set_target_properties(line PROPERTIES
        LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
    )
endif()