add_executable(${PROJECT}_check
main.cc
)

target_link_libraries(${PROJECT}_check PUBLIC ${PROJECT})
add_custom_target(check COMMAND $<TARGET_FILE:${PROJECT}_check> DEPENDS ${PROJECT}_check)
