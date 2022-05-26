cmake_minimum_required(VERSION 3.10)

project(colorful)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_INSTALL_PREFIX /usr/local)

install(FILES ${CMAKE_SOURCE_DIR}/src/include/colorful.hpp DESTINATION include/artwork/colorful/)