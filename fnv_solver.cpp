#include <fnv_solver.hpp>
#include <stp/c_interface.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

FNVSolver::FNVSolver(const FNVParam& _param, const FNVAlgo& _algo, 
                     const Constraint& _constraint, const int _startLength) :
  solved(false), startLength(_startLength), solutionLength(-1), param(_param), algo(_algo), constraint(_constraint)
{
}

void FNVSolver::solve()
{
  int length = startLength;

  while(!solved)
  {
    const int width = param.getWidth();
    VC checker = vc_createValidityChecker();

    const Expr basis = vc_bvConstExprFromDecStr(checker, width, param.getBasisCStr());
    const Expr prime = vc_bvConstExprFromDecStr(checker, width, param.getPrimeCStr());
    const Expr zeroPrefix = vc_bvConstExprFromInt(checker, width-8, 0);

    Expr input = vc_varExpr1(checker, "input", 0, 8*length);
    Expr hash = basis;

    for(int octet=length-1; octet>=0; --octet)
    {
      const Expr octetValue = vc_bvExtract(checker, input, 8*octet+7, 8*octet);
      constraint(checker, octetValue);
      const Expr extendedOctet = vc_bvConcatExpr(checker, zeroPrefix, octetValue);
      hash = algo(checker, hash, prime, extendedOctet);
    }

    const Expr zeroResult = vc_bvConstExprFromInt(checker, width, 0);
    const Expr isZero = vc_eqExpr(checker, hash, zeroResult);
    const Expr isNotZero = vc_notExpr(checker, isZero);
    const int queryResult = vc_query(checker, isNotZero);

    static const int INVALID=0, VALID=1, ERROR=2;
    if (queryResult == INVALID)
    {
      solved = true;
      solutionLength = length;
      const Expr data = vc_getCounterExample(checker, input);

      unsigned long bufferSize;
      char* bufferAddress;
      vc_printExprToBuffer(checker, data, &bufferAddress, &bufferSize);
      std::cout << bufferAddress << std::endl;
      free(bufferAddress);
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
