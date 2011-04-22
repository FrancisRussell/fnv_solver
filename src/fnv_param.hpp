#ifndef FNV_PARAM_HPP
#define FNV_PARAM_HPP

#include <vector>
#include <string>

class FNVParam
{
private:
  int size;
  std::string basis;
  std::string prime;

  FNVParam(const int size, const char* basis, const char* prime);

public:
  static std::vector<FNVParam> getAll();
  int getWidth() const;
  const char* getBasisCStr() const;
  const char* getPrimeCStr() const;
};

#endif
