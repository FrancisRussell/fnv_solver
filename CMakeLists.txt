cmake_minimum_required(VERSION 2.8)
project(fnv_solver)

if (DEFINED CMAKE_HOST_UNIX)
  add_definitions(-Wall -Wno-long-long -pedantic -O2)
endif()

set (STP_INSTALL_PREFIX "$ENV{HOME}/opt/stp")
include_directories ("${STP_INSTALL_PREFIX}/include")
link_directories ("${STP_INSTALL_PREFIX}/lib")

add_subdirectory(src)
