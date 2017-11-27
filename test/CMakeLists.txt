add_executable(${PROJECT}_check
  connection_test.cc
)

target_include_directories(${PROJECT}_check PUBLIC ${CMAKE_SOURCE_DIR}/extern)
target_link_libraries(${PROJECT}_check PUBLIC ${PROJECT})
add_custom_target(check
  COMMAND /bin/bash -c "python ${CMAKE_SOURCE_DIR}/test/server.py 8000 5 &"
  COMMAND /bin/bash -c "sleep 1"
  COMMAND $<TARGET_FILE:${PROJECT}_check>
  DEPENDS ${PROJECT}_check
  COMMENT "Running tests"
)
