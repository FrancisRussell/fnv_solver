#include "fnv_param.hpp"
#include <vector>

FNVParam::FNVParam(const int _size, const char* _basis, const char* _prime) :
  size(_size), basis(_basis), prime(_prime)
{
}

std::vector<FNVParam> FNVParam::getAll()
{
  const FNVParam param32(
    32,
    "2166136261",
    "16777619");

  const FNVParam param64(
    64,
    "14695981039346656037",
    "1099511628211");

  const FNVParam param128(
    128,
    "144066263297769815596495629667062367629",
    "309485009821345068724781371");

  const FNVParam param256(
    256,
    "100029257958052580907070968620625704837092796014241193945225284501741471925557",
    "374144419156711147060143317175368453031918731002211");

  const FNVParam param512(
    512,
    "96593031294966694980094354007163104660904187456726378961083743294344626579945829"
    "32197716438449813051892206539805784495328239340083876191928701583869517785",
    "35835915874844867368919076489095108449946327955754392558399825615420669938882575"
    "126094039892345713852759");

  const FNVParam param1024(
    1024,
    "14197795064947621068722070641403218320880622795441933960878474914617582723252296"
    "73230371772215086409652120235554936562817466910857181476047101507614802975596980"
    "40773201576924585630032153049571501574036444603635505054127112859663616102678680"
    "82893823963790439336411086884584107735010676915",
    "50164565101131186554345988110352789550307653454047907443030175238311120551081474"
    "51509157692220295382716162651878526895249385292291816524375083746691371804094271"
    "873160484737966720260389217684476157468082573");

  std::vector<FNVParam> params;
  params.push_back(param32);
  params.push_back(param64);
  params.push_back(param128);
  params.push_back(param256);
  params.push_back(param512);
  params.push_back(param1024);
  return params;
}

int FNVParam::getWidth() const
{
  return size;
}

const char* FNVParam::getBasisCStr() const
{
  return basis.c_str();
}

const char* FNVParam::getPrimeCStr() const
{
  return prime.c_str();
}
