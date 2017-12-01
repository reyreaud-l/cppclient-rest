include_directories(${CMAKE_SOURCE_DIR}/extern/test)

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

  add_test(NAME "${testcase}_default" COMMAND ${testcase})
  add_dependencies(check "${testcase}")

endforeach()
