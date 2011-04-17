#ifndef FNV_SOLVER_HPP
#define FNV_SOLVER_HPP

#include "fnv_param.hpp"
#include "fnv_algo.hpp"
#include "constraint.hpp"

class FNVSolver
{
private:
  bool solved;
  int startLength;
  int solutionLength;
  FNVParam param;
  FNVAlgo algo;
  Constraint constraint;

public:
  FNVSolver(const FNVParam& param, const FNVAlgo& algo, const Constraint& constraint, int startLength = 0);
  void solve();
  int getSolutionLength() const;
};

#endif
