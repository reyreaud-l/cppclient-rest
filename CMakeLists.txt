cmake_minimum_required(VERSION 3.1.0)

set(PROJECT cppclient-rest)
set(CURL_LIBRARY "-lcurl") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

find_package(CURL REQUIRED) 

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/mandatory)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

install(DIRECTORY include/cppclient DESTINATION /usr/local/include)
install(FILES  DESTINATION lib)
