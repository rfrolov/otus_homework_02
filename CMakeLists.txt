cmake_minimum_required(VERSION 3.2)

project(ip_filter_ VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

enable_testing()