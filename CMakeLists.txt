cmake_minimum_required(VERSION 3.0.0)
project(zkxjwm VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

include(C:/Users/Carter/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(toml11 CONFIG REQUIRED)

add_executable(zkxjwm ${SOURCES}
        src/display.cpp
        src/incl/display.h
        src/incl/vec.h
        src/config.cpp
        src/incl/config.h
        src/incl/windowconfig.h
)
set(EXECUTABLE_OUTPUT_PATH binary/)

target_include_directories(zkxjwm PUBLIC src/incl)

target_link_libraries(zkxjwm PRIVATE toml11::toml11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


