#include "fnv_param.hpp"
#include "fnv_algo.hpp"
#include "constraint.hpp"
#include "fnv_solver.hpp"
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>

int main(int argc, char** argv)
{
  const std::vector<FNVParam> fnvParams = FNVParam::getAll();
  const std::vector<FNVAlgo> fnvAlgos = FNVAlgo::getAll();
  const std::vector<Constraint> constraints = Constraint::getAll();

  BOOST_FOREACH(const FNVParam& fnvParam, fnvParams)
  {
    std::cout << "Problem size: " << fnvParam.getWidth() << std::endl;

    BOOST_FOREACH(const FNVAlgo& fnvAlgo, fnvAlgos)
    {
      std::cout << "Algorithm: " << fnvAlgo.getName() << std::endl;

      const Constraint nullConstraint = Constraint::getNull();
      std::cout << "Constraint: " << nullConstraint.getName() << std::endl;
      FNVSolver solver(fnvParam, fnvAlgo, nullConstraint);
      solver.solve();

      BOOST_FOREACH(const Constraint& constraint, constraints)
      {
        std::cout << "Constraint: " << constraint.getName() << std::endl;
        FNVSolver solver(fnvParam, fnvAlgo, constraint);
        solver.solve();
      }
    }
  }
}
