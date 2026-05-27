#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iomanip>
#include <iostream>

namespace afanasev
{
  class DataStruct
  {
  public:
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

  struct Kavichki
  {
    std::string & str;
  };

  std::istream & operator>>(std::istream & in, DataStruct & str);
  std::ostream & operator<<(std::ostream & out, const DataStruct & str);

  bool operator<(const DataStruct & lhs, const DataStruct & rhs);

  std::istream & operator>>(std::istream & in, CharExpect && str);
  std::istream & operator>>(std::istream & in, StringMatch && str);
  std::istream & operator>>(std::istream & in, ULLIn && str);
  std::istream & operator>>(std::istream & in, RacionalNum && str);
  std::istream & operator>>(std::istream & in, Kavichki && str);
}

std::istream & afanasev::operator>>(std::istream & in, DataStruct & str)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  DataStruct tmp{0, {0, 1}, ""};
  bool gotKey1 = false, gotKey2 = false, gotKey3 = false;

  in >> CharExpect{'('};
  while (in && (!gotKey1 || !gotKey2 || !gotKey3))
  {
    std::string label;
    in >> label;
    if (label == ":key1" && !gotKey1)
    {
      in >> ULLIn{tmp.key1};
      if (in)
      {
        gotKey1 = true;
      }
    }
    else if (label == ":key2" && !gotKey2)
    {
      in >> RacionalNum{tmp.key2};
      if (in)
      {
        gotKey2 = true;
      }
    }
    else if (label == ":key3" && !gotKey3)
    {
      in >> Kavichki{tmp.key3};
      if (in)
      {
        gotKey3 = true;
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
      break;
    }
  }

  in >> StringMatch{":)"};
  if (in && gotKey1 && gotKey2 && gotKey3)
  {
    str = tmp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream & afanasev::operator<<(std::ostream & out, const DataStruct & str)
{
  std::ostream::sentry s(out);
  if (!s)
  {
    return out;
  }

  out << "(:key1 " << str.key1 << "ull"
    << ":key2 (:N " << str.key2.first << ":D " << str.key2.second << ":)"
    << ":key3 " << std::quoted(str.key3) << ":)";
  return out;
}

bool afanasev::operator<(const DataStruct & lhs, const DataStruct & rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }

  long double lval = static_cast< long double >(lhs.key2.first) / lhs.key2.second;
  long double rval = static_cast< long double >(rhs.key2.first) / rhs.key2.second;
  if (lval != rval)
  {
    return lval < rval;
  }
  return lhs.key3.size() < rhs.key3.size();
}

std::istream & afanasev::operator>>(std::istream & in, CharExpect && str);
std::istream & afanasev::operator>>(std::istream & in, StringMatch && str);
std::istream & afanasev::operator>>(std::istream & in, ULLIn && str);
std::istream & afanasev::operator>>(std::istream & in, RacionalNum && str);
std::istream & afanasev::operator>>(std::istream & in, Kavichki && str);

#endif
