include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(triangle triangle.cpp)
add_executable(rect rect.cpp)
add_executable(line drawLine.cpp)
add_executable(quad drawQuad.cpp)
target_link_libraries(line PRIVATE glfw glad::glad)
target_link_libraries(quad PRIVATE glfw glad::glad)

set(exes triangle rect)
foreach(exe ${exes})
  target_link_libraries(${exe} PRIVATE util glfw glad::glad)
endforeach()

# 仅当使用MSVC编译器时设置/SUBSYSTEM:WINDOWS，关闭控制台窗口
if(MSVC)
    set_target_properties(${exes} PROPERTIES
        LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS"
    )
endif()