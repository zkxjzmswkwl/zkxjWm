cmake_minimum_required(VERSION 3.0.0)
project(zkxjwm VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

include(CTest)
enable_testing()

file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(zkxjwm ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
