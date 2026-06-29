#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>

namespace afanasev
{
  struct DelimIO
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, DelimIO && delim)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }

    char c = 0;
    in >> c;
    if (in && c != delim.expected)
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }
}

#endif
