add_executable(triangle triangle.cpp)
add_executable(rect rect.cpp)
add_executable(line drawLine.cpp)
add_executable(quad drawQuad.cpp)

target_link_libraries(triangle PRIVATE util glfw glad::glad)
target_link_libraries(rect PRIVATE util glfw glad::glad)
target_link_libraries(line PRIVATE util glfw glad::glad)
target_link_libraries(quad PRIVATE util glfw glad::glad)

set(exes triangle rect line quad)
# 仅当使用MSVC编译器时设置/SUBSYSTEM:WINDOWS
if(MSVC)
    set_target_properties(${exes} PROPERTIES
        LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
    )
endif()