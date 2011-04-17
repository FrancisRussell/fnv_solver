#include <constraint.hpp>
#include <vector>
#include <cassert>
#include <stp/c_interface.h>

Constraint::Constraint(const char* _name, const constraint_function_t _function) :
  name(_name), function(_function)
{
}

Expr Constraint::constrainRange(VC& vc, const Expr& e, const int lower, const int upper)
{
  assert(getVWidth(e) == 8);
  assert(lower <= upper);
  assert(lower >= 0 && upper < 256);
  assert(lower >= 0 && upper < 256);

  const Expr lowerExpr = vc_bvConstExprFromInt(vc, 8, lower);
  const Expr upperExpr = vc_bvConstExprFromInt(vc, 8, upper);

  const Expr check = vc_andExpr(vc,
                       vc_bvGeExpr(vc, e, lowerExpr),
                       vc_bvLeExpr(vc, e, upperExpr));
  return check;
}

Constraint Constraint::getNull()
{
  return Constraint("None", &none);
}

Expr Constraint::none(VC& vc, const Expr& e)
{
  assert(getVWidth(e) == 8);
  return vc_trueExpr(vc);
}

Expr Constraint::nonNulASCII(VC& vc, const Expr& e)
{
  assert(getVWidth(e) == 8);
  const Expr zero = vc_bvConstExprFromInt(vc, 8, 0);
  const Expr upper = vc_bvConstExprFromInt(vc, 8, 128);
  const Expr check = vc_andExpr(vc,
                       vc_notExpr(vc, vc_eqExpr(vc, e, zero)),
                       vc_eqExpr(vc, vc_bvAndExpr(vc, upper, e), zero));
  return check;
}

Expr Constraint::printableASCII(VC& vc, const Expr& e)
{
  assert(getVWidth(e) == 8);
  return constrainRange(vc, e, 0x20, 0x7e);
}

Expr Constraint::alphanumericASCII(VC& vc, const Expr& e)
{
  assert(getVWidth(e) == 8);
  Expr result = constrainRange(vc, e, 0x30, 0x39);
  result = vc_orExpr(vc, result, constrainRange(vc, e, 0x41, 0x5a));
  result = vc_orExpr(vc, result, constrainRange(vc, e, 0x60, 0x7a));
  return result;
}

std::string Constraint::getName() const
{
  return name;
}

std::vector<Constraint> Constraint::getAll()
{
  std::vector<Constraint> constraints;
  constraints.push_back(Constraint("Non-NUL ASCII", &nonNulASCII));
  constraints.push_back(Constraint("Printable ASCII", &printableASCII));
  constraints.push_back(Constraint("Alphanumeric ASCII", &alphanumericASCII));
  return constraints;
}

void Constraint::operator()(VC& vc, const Expr& e) const
{
  vc_assertFormula(vc, function(vc, e));
}
