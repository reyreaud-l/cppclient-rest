add_library(${PROJECT} SHARED
  connection.cc
  response.cc
  helper.cc
)

target_include_directories(${PROJECT} PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT} PUBLIC ${CURL_LIBRARIES})
