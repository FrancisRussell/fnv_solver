#ifndef FNV_ALGO_HPP
#define FNV_ALGO_HPP

#include <vector>
#include <string>
#include <stp/c_interface.h>

class FNVAlgo
{
private:
  typedef Expr(*mix_function_t)(VC& vc, const Expr&, const Expr&, const Expr&);
  static Expr fnv1(VC& vc, const Expr& hash, const Expr& prime, const Expr& octet);
  static Expr fnv1a(VC& vc, const Expr& hash, const Expr& prime, const Expr& octet);
  std::string name;
  mix_function_t function;

  FNVAlgo(const char* _name, mix_function_t _function);

public:
  static std::vector<FNVAlgo> getAll();

  std::string getName() const;
  Expr operator()(VC& vc, const Expr& hash, const Expr& prime, const Expr& octet) const;
};

#endif
