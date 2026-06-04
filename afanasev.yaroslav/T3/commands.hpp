#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <cctype>
#include "shape.hpp"

namespace afanasev
{
  void area(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
  void max(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
  void min(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
  void count(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
  void perms(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
  void rects(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons);
}

namespace
{
  using namespace afanasev;

  double getArea(const Polygon & p)
  {
    return area(p);
  }

  bool isEven(const Polygon & p)
  {
    return p.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon & p)
  {
    return p.points.size() % 2 != 0;
  }

  bool hasVertexCount(const Polygon & p, size_t n)
  {
    return p.points.size() == n;
  }

  bool isDigitChar(char c)
  {
    return std::isdigit(static_cast< unsigned char >(c));
  }

  bool isNumber(const std::string & s)
  {
    return !s.empty() && std::all_of(s.begin(), s.end(), isDigitChar);
  }

  template < class Pred >
  void printFilteredSum(std::ostream & out, const std::vector< Polygon > & polygons, Pred pred)
  {
    std::vector< Polygon > filtered;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtered), pred);
    std::vector< double > areas;
    areas.reserve(filtered.size());
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(areas), getArea);
    out << std::fixed << std::setprecision(1)
      << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
  }

  bool areaLess(const Polygon & a, const Polygon & b)
  {
    return area(a) < area(b);
  }

  bool vertexLess(const Polygon & a, const Polygon & b)
  {
    return a.points.size() < b.points.size();
  }
}


void afanasev::area(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("invalid");
  }
  out << std::fixed << std::setprecision(1);

  if (param == "MEAN")
  {
    if (polygons.empty()) throw std::invalid_argument("invalid");
    std::vector< double > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << sum / polygons.size() << "\n";
  }

  else if (param == "EVEN")
  {
    printFilteredSum(out, polygons, isEven);
  }
  else if (param == "ODD")
  {
    printFilteredSum(out, polygons, isOdd);
  }
  else if (isNumber(param))
  {
    size_t n = std::stoul(param);
    if (n < 3) throw std::invalid_argument("invalid");
    printFilteredSum(out, polygons, std::bind(hasVertexCount, std::placeholders::_1, n));
  }
  else
  {
    throw std::invalid_argument("invalid");
  }
}

void afanasev::max(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{
  std::string param;
  if (!(in >> param)) throw std::invalid_argument("invalid");
  if (polygons.empty()) throw std::invalid_argument("invalid");

  if (param == "AREA")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(), areaLess);
    out << std::fixed << std::setprecision(1) << area(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(), vertexLess);
    out << it->points.size() << "\n";
  }
  else
  {
    throw std::invalid_argument("invalid");
  }
}

void afanasev::min(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{
  std::string param;
  if (!(in >> param))
  {
    throw std::invalid_argument("invalid");
  }
  if (polygons.empty())
  {
    throw std::invalid_argument("invalid");
  }

  if (param == "AREA")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(), areaLess);
    out << std::fixed << std::setprecision(1) << calculateArea(*it) << "\n";
  }
  else if (param == "VERTEXES")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(), vertexLess);
    out << it->points.size() << "\n";
  }
  else
  {
    throw std::invalid_argument("invalid");
  }
}

void afanasev::count(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{
  
}

void afanasev::perms(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{
  
}

void afanasev::rects(std::istream & in, std::ostream & out, const std::vector< Polygon > & polygons)
{

}

#endif
