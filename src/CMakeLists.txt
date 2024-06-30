FILE(GLOB SOURCE_FILES *.cpp)
add_library(util STATIC ${SOURCE_FILES})
target_link_libraries(util PRIVATE glfw lodepng)
