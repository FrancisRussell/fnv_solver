include_directories ("${STP_INCLUDE_DIRS}")
add_executable(solver solver.cpp constraint.cpp fnv_algo.cpp fnv_param.cpp fnv_solution.cpp fnv_solver.cpp)
target_link_libraries(solver ${STP_LIBRARIES})
