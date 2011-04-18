cmake_minimum_required(VERSION 2.8)
project(fnv_solver)

if (DEFINED CMAKE_HOST_UNIX)
  add_definitions(-Wall -Wno-long-long -pedantic -O2)
endif()

include_directories ("${PROJECT_SOURCE_DIR}")

set (STP_INSTALL_PREFIX "$ENV{HOME}/opt/stp")
include_directories ("${STP_INSTALL_PREFIX}/include")
link_directories ("${STP_INSTALL_PREFIX}/lib")

add_executable(solver solver.cpp constraint.cpp fnv_algo.cpp fnv_param.cpp fnv_solution.cpp fnv_solver.cpp)
target_link_libraries(solver stp)
