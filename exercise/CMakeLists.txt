include_directories(../src)
# Get a list of all .cpp files
file(GLOB EXERCISE_FILES "*.cpp")
foreach(CPP_FILE ${EXERCISE_FILES})
    # Get the filename without directory or extension
    get_filename_component(CPP_FILE_WE ${CPP_FILE} NAME_WE)
    # Add compile target
    add_executable(${CPP_FILE_WE} ${CPP_FILE})
    # Link to the library
    target_link_libraries(${CPP_FILE_WE} PRIVATE util glfw glad::glad)
endforeach()