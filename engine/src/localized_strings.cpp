//
//  localized_strings.cpp
//  Codex
//
//  Created by Jens Kwasniok on 20.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "localized_strings.h"

using namespace cdx;

localized_strings* localized_strings::current = nullptr;

void localized_strings::set(cdx::localized_strings* ls)
{
	current = ls;
}

bool localized_strings::set_language_id(const std::string &lang_id)
{
	if (language_id.empty()) {
		language_id = lang_id;
		return true;
	}
	else
	{
		return false;
	}
}

void localized_strings::add_str(std::pair<int, std::string> &isp)
{
	auto it = strings.find(isp.first);
	if (it != strings.end())
	{
		LOG_NORMAL("Redefinition of a loalized string with id=%i.", isp.first);
	}

	strings[isp.first] = isp.second;
}

std::string localized_strings::get_str(const int number) const
{
	std::string s;
	auto it = strings.find(number);
	if (it != strings.end())
	{
		s = it->second;
	}
	else
	{
		LOG_NORMAL("No localized string found for id=%i", number);
		s += "~UNKNOWN LOCALIZED STRING FOR N=";
		s += number;
		s+= "~";
	}

	return s;
}

bool cdx::create_localized_strings_from_file(cdx::localized_strings& ls, const std::string& file_path)
{
	bool good = false;
	std::ifstream ifs (file_path);
	if (ifs.good())
	{
		ifs >> ls;
		good = true;
	}
	else
	{
		LOG_NORMAL("Uninitialized localized strings set! Could not open file: %s", file_path.c_str());
	}
	ifs.close();

	return good;
}

std::istream& operator>>(std::istream& is, cdx::localized_strings& ls)
{
	// language identifier:
	std::string lang_id;
	is >> lang_id;
	ls.set_language_id(lang_id);

	// id string list:
	std::pair<int, std::string> p;
	char c;

	do
	{
		is >> p;
		if (!is.good()) break;
		is >> c;
		if (c != ';')
		{
			is.setf(std::ios_base::failbit);
		}
		if (!is.good()) break;
		ls.add_str(p);
	}
	while (is.good());

	return is;
}

std::ostream& operator<<(std::ostream& os, cdx::localized_strings& ls)
{
	// language identifier:
	os << ls.get_language_id() << std::endl;

	// id string list:
	std::pair<int, std::string> p;
	for (auto it : ls.get_all())
	{
		p.first = it.first;
		p.second = it.second;
		os << p;
		os << ";" << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, std::pair<int, std::string>& p)
{
	std::pair<int, std::string> tmp;

	char c;
	is >> tmp.first;
	is >> c;
	if (c != ',')
	{
		is.setf(std::ios_base::failbit);
		return is;
	}
	is >> c;
	if (c != '"')
	{
		is.setf(std::ios_base::failbit);
		return is;
	}
	while (c = is.get(), c != '"')
	{
		tmp.second += c;
	}

	if (is.good())
	{
		p = tmp;
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, std::pair<int, std::string>& p)
{
	os << p.first << ", \"" << p.second << "\"";

	return os;
}