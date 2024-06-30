add_executable(texture imageTexture.cpp)
target_include_directories(texture PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(texture PRIVATE util glfw glad::glad)