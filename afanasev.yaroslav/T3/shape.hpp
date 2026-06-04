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
    char c = 0;
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

  double makeArea(const Polygon & polygon);
  Polygon swapCoordinates(const Polygon & p);
  std::vector< Point > normalize(const Polygon & p);
  bool isPermutationOf(const Polygon & a, const Polygon & b);
  bool isRectangle(const Polygon & poly);
}

bool afanasev::isRectangle(const Polygon & poly)
{
  const auto & pts = poly.points;
  if (pts.size() != 4)
  {
    return false;
  }

  auto dot = [](const Point & p1, const Point & p2, const Point & p3)
  {
    int dx1 = p2.x - p1.x;
    int dy1 = p2.y - p1.y;
    int dx2 = p3.x - p2.x;
    int dy2 = p3.y - p2.y;
    return dx1 * dx2 + dy1 * dy2;
  };

  for (size_t i = 0; i < 4; ++i)
  {
    const Point & a = pts[i];
    const Point & b = pts[(i + 1) % 4];
    const Point & c = pts[(i + 2) % 4];
    if (dot(a, b, c) != 0)
    {
      return false;
    }
  }
  return true;
}

bool afanasev::isPermutationOf(const Polygon & a, const Polygon & b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }
  return normalize(a) == normalize(b);
}

std::vector< afanasev::Point > afanasev::normalize(const Polygon & p)
{
  std::vector< Point > pts = p.points;
  if (pts.empty())
  {
    return pts;
  }

  int minX = std::min_element(pts.begin(), pts.end(),
    [](const Point & a, const Point & b) { return a.x < b.x; })->x;
  int minY = std::min_element(pts.begin(), pts.end(),
    [](const Point & a, const Point & b) { return a.y < b.y; })->y;
  for (auto & p : pts)
  {
    p.x -= minX; p.y -= minY;
  }
  std::sort(pts.begin(), pts.end(),
    [](const Point & a, const Point & b)
    {return a.x < b.x || (a.x == b.x && a.y < b.y);});

  return pts;
}

afanasev::Polygon afanasev::swapCoordinates(const Polygon & p)
{
  Polygon res;
  res.points.reserve(p.points.size());
  std::transform(p.points.begin(), p.points.end(), std::back_inserter(res.points),
    [](const Point & p)
    {return Point{p.y, p.x};});
  return res;
}

double afanasev::makeArea(const Polygon & polygon)
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
