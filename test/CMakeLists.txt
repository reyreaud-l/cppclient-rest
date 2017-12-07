# Download and unpack googletest at configure time
file(MAKE_DIRECTORY googletest-download)
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND cmake .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
  ${CMAKE_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL)

set(TEST ${PROJECT}_test)

set(TEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${TEST_COMMAND} COMMENT "Running tests")

file(GLOB FILES "*_test.cc")
foreach(file ${FILES})
  get_filename_component(file_basename ${file} NAME_WE)
  string(REGEX REPLACE "([^$]+)_test" "test-\\1" testcase ${file_basename})

  add_executable(${testcase} EXCLUDE_FROM_ALL ${file})
  target_include_directories(${testcase} PRIVATE ${CMAKE_SOURCE_DIR}/extern/test)
  target_link_libraries(${testcase} PRIVATE ${PROJECT})
  target_link_libraries(${testcase} PRIVATE gtest_main)
  target_compile_options(${testcase} PRIVATE -std=c++11 -Wall -Wextra -Werror -pedantic)

  add_test(NAME "${testcase}_default" COMMAND ${testcase})
  add_dependencies(check "${testcase}")

endforeach()
