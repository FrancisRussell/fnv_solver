STP_INSTALL_DIR = ${HOME}/opt/stp
CXXFLAGS=-I. -I${STP_INSTALL_DIR}/include -O2

HEADERS = constraint.hpp fnv_algo.hpp fnv_param.hpp fnv_solver.hpp fnv_solution.hpp
OBJECTS = constraint.o fnv_algo.o fnv_param.o fnv_solver.o solver.o fnv_solution.o

solver: ${HEADERS} ${OBJECTS}
	${CXX} ${OBJECTS} -L${STP_INSTALL_DIR}/lib -lstp -o $@

clean:
	rm -f ${OBJECTS}

.PHONY: clean
