#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include <string>
#include <vector>
#include <stp/c_interface.h>

class Constraint
{
private:
  typedef Expr(*constraint_function_t)(VC& vc, const Expr&);
  static Expr none(VC& vc, const Expr& e);
  static Expr nonNulASCII(VC& vc, const Expr& e);
  static Expr printableASCII(VC& vc, const Expr& e);
  static Expr alphanumericASCII(VC& vc, const Expr& e);
  static Expr constrainRange(VC& vc, const Expr& e, const int lower, const int upper);

  std::string name;
  constraint_function_t function;
  
  Constraint(const char* name, constraint_function_t function);

public:
  static Constraint getNull();
  static std::vector<Constraint> getAll();
  std::string getName() const;
  void operator()(VC& vc, const Expr& e) const;
};

#endif
