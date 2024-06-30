set(examples "${examples}")

# Process subdirectories
foreach(example ${examples})
  if(EXISTS ${PROJECT_SOURCE_DIR}/examples/${example}/CMakeLists.txt)
    message(STATUS "Processing examples/${example}")
    add_subdirectory(${example})
  else()
    message(${HIGHLIGHTED_STATUS}
      "Skipping src/${example}: it does not contain a CMakeLists.txt file"
    )
  endif()
endforeach()