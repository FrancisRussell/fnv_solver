#ifndef FNV_SOLUTION_HPP
#define FNV_SOLUTION_HPP

#include <cassert>
#include <vector>
#include <ostream>
#include <stp/c_interface.h>
#include "fnv_param.hpp"
#include "fnv_algo.hpp"

class FNVSolution
{
private:
  std::string prefix;
  std::vector<unsigned char> octets;

public:
  FNVSolution(const FNVParam& param, const FNVAlgo& algo, VC& vc, const std::vector<Expr>& octets);
  bool operator<(const FNVSolution& s) const;
  bool operator==(const FNVSolution& s) const;
  void write(std::ostream& o) const;
};

std::ostream& operator<<(std::ostream& o, const FNVSolution& s);

#endif
