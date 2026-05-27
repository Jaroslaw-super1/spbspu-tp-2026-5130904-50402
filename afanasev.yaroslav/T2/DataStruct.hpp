#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace afanasev
{
  class DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct CharExpect
  {
    char exp;
  };

  struct StringMatch
  {
    std::string exp;
  };

  struct ULLIn
  {
    unsigned long long & num;
  };

  struct RacionalNum
  {
    std::pair< long long, unsigned long long > & num;
  };

  struct kavichki
  {
    std::string & str;
  };

  std::istream & operator>>(std::istream & in, DataStruct & str);
  std::ostream & operator<<(std::ostream & out, const DataStruct & str);

  std::istream & operator>>(std::istream & in, CharExpect && str);
  std::istream & operator>>(std::istream & in, StringMatch && str);
  std::istream & operator>>(std::istream & in, ULLIn && str);
  std::istream & operator>>(std::istream & in, RacionalNum && str);
  std::istream & operator>>(std::istream & in, kavichki && str);
}

std::istream & afanasev::operator>>(std::istream & in, DataStruct & str);
std::ostream & afanasev::operator<<(std::ostream & out, const DataStruct & str);

std::istream & afanasev::operator>>(std::istream & in, CharExpect && str);
std::istream & afanasev::operator>>(std::istream & in, StringMatch && str);
std::istream & afanasev::operator>>(std::istream & in, ULLIn && str);
std::istream & afanasev::operator>>(std::istream & in, RacionalNum && str);
std::istream & afanasev::operator>>(std::istream & in, kavichki && str);

#endif
