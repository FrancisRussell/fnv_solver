#include "fnv_solver.hpp"
#include "fnv_solution.hpp"
#include <stp/c_interface.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <string>

FNVSolver::FNVSolver(const FNVParam& _param, const FNVAlgo& _algo, 
                     const Constraint& _constraint, const int _startLength) :
  solved(false), startLength(_startLength), solutionLength(-1), param(_param), algo(_algo), constraint(_constraint)
{
}

std::string FNVSolver::getOctetName(const int index)
{
  std::ostringstream octetName;
  octetName << "input_" << index;
  return octetName.str();
}

void FNVSolver::solve()
{
  int length = startLength;

  while(!solved)
  {
    std::cout << "Searching for solutions of length " << length << "..." << std::endl;
    const int width = param.getWidth();
    VC checker = vc_createValidityChecker();

    const Expr basis = vc_bvConstExprFromDecStr(checker, width, param.getBasisCStr());
    const Expr prime = vc_bvConstExprFromDecStr(checker, width, param.getPrimeCStr());
    const Expr zeroPrefix = vc_bvConstExprFromDecStr(checker, width-8, "0");
    const Expr zeroResult = vc_bvConstExprFromDecStr(checker, width, "0");

    Expr hash = basis;
    std::vector<Expr> inputOctets;
    inputOctets.reserve(length);

    for(int octet=0; octet<length; ++octet)
    {
      const std::string octetName = getOctetName(octet);
      const Expr inputOctet = vc_varExpr1(checker, octetName.c_str(), 0, 8);
      inputOctets.push_back(inputOctet);

      constraint(checker, inputOctet);
      const Expr extendedOctet = vc_bvConcatExpr(checker, zeroPrefix, inputOctet);
      hash = algo(checker, hash, prime, extendedOctet);
    }

    const Expr isZero = vc_eqExpr(checker, hash, zeroResult);
    const Expr isNotZero = vc_notExpr(checker, isZero);
    const int queryResult = vc_query(checker, isNotZero);

    static const int INVALID=0, VALID=1, ERROR=2;
    if (queryResult == INVALID)
    {
      solved = true;
      solutionLength = length;
      FNVSolution solution(param, algo, checker, inputOctets);
      std::cout << solution << std::endl;
    }
    else if (queryResult == ERROR)
    {
      std::cerr << "Error during query." << std::endl;
      exit(EXIT_FAILURE);
    }

    vc_Destroy(checker);
    ++length;
  }
}

int FNVSolver::getSolutionLength() const
{
  assert(solved);
  return solutionLength;
}
