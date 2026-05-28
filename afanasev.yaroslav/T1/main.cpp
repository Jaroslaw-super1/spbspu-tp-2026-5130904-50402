#include <iostream>
#include <string>
#include <unordered_map>
#include "command.hpp"
#include "note.hpp"

int main()
{
  afanasev::note_t db;

  const std::unordered_map< std::string, afanasev::func_t > cmds
  {
    {"note", afanasev::noteCmd},
    {"line", afanasev::lineCmd},
    {"show", afanasev::showCmd},
    {"drop", afanasev::dropCmd},

    {"link", afanasev::linkCmd},
    {"halt", afanasev::haltCmd},
    {"mind", afanasev::mindCmd},
    {"expired", afanasev::expiredCmd},
    {"refresh", afanasev::refreshCmd},
  };

  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout, db);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.ignore(afanasev::streamMax, '\n');
    }
  }

  if (!std::cin.eof())
  {
    std::cerr << "Error input" << '\n';
    return 1;
  }

  return 0;
}
