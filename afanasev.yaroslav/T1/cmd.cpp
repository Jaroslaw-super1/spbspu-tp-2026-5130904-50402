#include <iostream>
#include <unordered_map>
#include "cmd.hpp"
#include "note.hpp"

#include <iosfwd>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>

void afanasev::noteCmd(std::istream & in, std::ostream &, note_t & db)
{
	std::string name;
	in >> name;

	if (db.find(name) == db.end())
	{
		db[name] = std::make_shared< Note >();
	}
	else
	{
		throw std::logic_error("This note have");
	}
}

void afanasev::lineCmd(std::istream & in, std::ostream &, note_t & db)
{
	std::string name, text;
	in >> name;

	in >> std::quoted(text);

  try
	{
    db.at(name)->text_.push_back(text);
  }
	catch (const std::out_of_range &)
	{
    throw std::logic_error("not have note with this name");
  }
}

void afanasev::showCmd(std::istream & in, std::ostream & out, note_t & db)
{
	std::string name;
	in >> name;

	try
	{
		for (const std::string & line : db.at(name)->text_)
		{
			out << line << '\n';
		}
	}
	catch (const std::out_of_range &)
	{
		throw std::logic_error("not have note with this name");
	}
}

void afanasev::dropCmd(std::istream & in, std::ostream &, note_t & db)
{
	std::string name;
	in >> name;

	db.erase(name);
}


void afanasev::linkCmd(std::istream & in, std::ostream & out, note_t & db)
{
	std::string name, link;
	in >> name >> link;

	try
	{
		if (db.at(name)->ptr_.find(link) == db.at(name)->ptr_.end())
		{
			db.at(name)->ptr_[link] = db.at(link);
		}
		else
		{
			throw std::logic_error("This link already exists");
		}
	}
	catch(const std::out_of_range &)
	{
		throw std::logic_error("error linking");
	}
}

void afanasev::haltCmd(std::istream & in, std::ostream & out, note_t & db)
{
	std::string name, link;
	in >> name >> link;

	try
	{
		db.at(name)->ptr_.erase(link);
	}
	catch(const std::out_of_range &)
	{
		throw std::logic_error("Not have link on this note");
	}
}

void afanasev::mindCmd(std::istream & in, std::ostream & out, note_t & db)
{
	std::string name;
	in >> name;

	try
	{
		for (const std::pair< const std::string, std::weak_ptr< Note > > & ptr : db.at(name)->ptr_)
		{
			if (!ptr.second.expired())
			{
				out << ptr.first << '\n';
			}
		}
	}
	catch(const std::out_of_range &)
	{
		throw std::logic_error("not have this name");
	}
}

void afanasev::expiredCmd(std::istream & in, std::ostream & out, note_t & db)
{
	size_t cnt = 0;
	std::string name;
	in >> name;

	try
	{
		for (const std::pair< const std::string, std::weak_ptr< Note > > & ptr : db.at(name)->ptr_)
		{
			if (ptr.second.expired())
			{
				++cnt;
			}
			
		}
	}
	catch(const std::out_of_range &)
	{
		throw std::logic_error("Not have link on this note");
	}
}

void afanasev::refreshCmd(std::istream & in, std::ostream & out, note_t & db)
{
	std::string name, link;
	in >> name >> link;

	try
	{
		db.at(name)->ptr_.erase(link);
	}
	catch(const std::out_of_range &)
	{
		throw std::logic_error("Not have link on this note");
	}
}
