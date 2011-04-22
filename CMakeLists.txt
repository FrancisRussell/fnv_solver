cmake_minimum_required(VERSION 2.8)
project(fnv_solver)

if (DEFINED CMAKE_HOST_UNIX)
  add_definitions(-Wall -Wno-long-long -pedantic -O2)
endif()

find_package(Boost)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Unable to locate Boost.")
endif()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(STP_INCLUDE_DIRS stp/c_interface.h
  DOC "The folder containing the STP header folder."
)

FIND_LIBRARY(STP_LIBRARIES
  NAMES stp
  DOC "The location of the STP library."
)

add_subdirectory(src)
