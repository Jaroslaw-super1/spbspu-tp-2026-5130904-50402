#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cctype>

namespace afanasev
{
  struct Point
  {
    int x, y;
  };

  bool operator==(const Point & lhs, const Point & rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct DelimIO
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, DelimIO && delim)
  {
    char c;
    in >> c;
    if (c != delim.expected)
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  class IOguard
  {
  public:
    IOguard(std::istream & stream) : stream_(stream), flags_(stream.flags()) {}
    ~IOguard() { stream_.flags(flags_); }
  private:
    std::istream & stream_;
    std::ios::fmtflags flags_;
  };

  std::istream & operator>>(std::istream & in, Point & point)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    Point pt;
    in >> DelimIO{'('} >> pt.x >> DelimIO{';'} >> pt.y >> DelimIO{')'};
    if (in)
    {
      point = pt;
    }

    return in;
  }

  std::istream & operator>>(std::istream & in, Polygon & polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    IOguard guard(in);
    size_t count = 0;
    if (!(in >> count) || count < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::vector< Point > points;
    points.reserve(count);
    std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(points));
    if (in)
    {
      polygon.points = std::move(points);
    }

    return in;
  }

  double area(const Polygon & polygon);
}

double afanasev::area(const Polygon & polygon)
{
  const auto & pts = polygon.points;
  size_t n = pts.size();
  if (n < 3)
  {
    return 0.0;
  }

  double sum = 0.0;
  for (size_t i = 0; i < n; ++i)
  {
    const Point & p1 = pts[i];
    const Point & p2 = pts[(i + 1) % n];
    sum += static_cast< double >(p1.x * p2.y - p2.x * p1.y);
  }

  return std::abs(sum) / 2.0;
}

bool afanasev::operator==(const Point & lhs, const Point & rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

#endif
