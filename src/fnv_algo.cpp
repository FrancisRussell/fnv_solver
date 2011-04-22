#include <stp/c_interface.h>
#include "fnv_algo.hpp"
#include <vector>
#include <string>
#include <cassert>

FNVAlgo::FNVAlgo(const char* _name, const mix_function_t _function) : 
  name(_name), function(_function)
{
}

std::string FNVAlgo::getName() const
{
  return name;
}

Expr FNVAlgo::fnv1(VC& checker, const Expr& hash, const Expr& prime, const Expr& octet)
{
  const int width = getVWidth(hash);
  assert(width == getVWidth(prime));
  assert(width == getVWidth(octet));

  Expr result = hash;
  result = vc_bvMultExpr(checker, getVWidth(hash), result, prime);
  result = vc_bvXorExpr(checker, result, octet);
  return result;
}

Expr FNVAlgo::fnv1a(VC& checker, const Expr& hash, const Expr& prime, const Expr& octet)
{
  const int width = getVWidth(hash);
  assert(width == getVWidth(prime));
  assert(width == getVWidth(octet));

  Expr result = hash;
  result = vc_bvXorExpr(checker, result, octet);
  result = vc_bvMultExpr(checker, getVWidth(hash), result, prime);
  return result;
}

std::vector<FNVAlgo> FNVAlgo::getAll()
{
  std::vector<FNVAlgo> algos;
  algos.push_back(FNVAlgo("1", &fnv1));
  algos.push_back(FNVAlgo("1a", &fnv1a));
  return algos;
}

Expr FNVAlgo::operator()(VC& vc, const Expr& hash, const Expr& prime, const Expr& octet) const
{
  return function(vc, hash, prime, octet);
}
