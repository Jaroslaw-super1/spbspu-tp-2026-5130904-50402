#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
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


#endif
