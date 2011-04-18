#include <cassert>
#include <vector>
#include <sstream>
#include <boost/foreach.hpp>
#include <fnv_solution.hpp>
#include <stp/c_interface.h>

FNVSolution::FNVSolution(const FNVParam& param, const FNVAlgo& algo, VC& vc, 
                         const std::vector<Expr>& octetExprs)
{
  std::ostringstream prefixStream;
  prefixStream << "FNV" << param.getWidth() << "_" << algo.getName();
  prefix = prefixStream.str();


  BOOST_FOREACH(const Expr& octetExpr, octetExprs)
  {
    assert(getVWidth(octetExpr) == 8);

    const Expr octetValue = vc_getCounterExample(vc, octetExpr);
    assert(getType(octetValue) == BITVECTOR_TYPE);
    assert(getExprKind(octetValue) == BVCONST);

    const unsigned value = getBVUnsigned(octetValue);
    assert(value < 256);

    octets.push_back(static_cast<unsigned char>(value));
  }
}

bool FNVSolution::operator<(const FNVSolution& s) const
{
  if (prefix < s.prefix)
    return true;

  if (prefix == s.prefix)
    return octets < s.octets;

  return false;
}

bool FNVSolution::operator==(const FNVSolution& s) const
{
  return prefix == s.prefix && octets == s.octets;
}

void FNVSolution::write(std::ostream& out) const
{
  out << prefix << "(";
  for(unsigned i=0; i<octets.size(); ++i)
  {
    const char octet = octets[i];
    static const char* digits = "0123456789abcdef";
    const char first = digits[octet >> 4];
    const char second = digits[octet & ((1<<4)-1)];
    out << first << second << (i+1 < octets.size() ? " " : "");
  }

  out << ")";
}

std::ostream& operator<<(std::ostream& o, const FNVSolution& solution)
{
  solution.write(o);
  return o;
}
