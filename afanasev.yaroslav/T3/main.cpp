#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <string>
#include <vector>
#include "commands.hpp"
#include "shape.hpp"

int main(int argc, char **argv)
{
  namespace af = afanasev;
  constexpr std::streamsize streamMax = std::numeric_limits< std::streamsize >::max();

  if (argc != 2)
  {
    std::cerr << "Incorrect parameters\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Error: cannot open file\n";
    return 1;
  }

  std::unordered_map< std::string, std::function< void() > > commands;



  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)();
    }
    catch (const std::exception &)
    {
      if (std::cin.fail())
      {
        std::cin.clear();
      }

      std::cin.ignore(streamMax, '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}