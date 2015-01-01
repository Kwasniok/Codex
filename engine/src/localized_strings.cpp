//
//  localized_strings.cpp
//  Codex
//
//  Created by Jens Kwasniok on 20.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "localized_strings.h"

using namespace cdx;

bool Localized_String_Map::set_language_id(const std::string &lang_id)
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

void Localized_String_Map::add_str(const int n, const std::string str)
{
	std::pair<int, std::string> isp = {n, str};
	add_str(isp);
}

void Localized_String_Map::add_str(std::pair<int, std::string> &isp)
{
	auto it = strings.find(isp.first);
	if (it != strings.end())
	{
		LOG_NORMAL("Redefinition of a loalized string for language=\"%s\" and id=%i.",
				   language_id.c_str(), isp.first);
	}

	strings[isp.first] = isp.second;
}

const char* Localized_String_Map::get_str(const int n) const
{
	auto it = strings.find(n);
	if (it != strings.end())
	{
		return it->second.c_str();
	}
	else
	{
		return NO_STRING_FOR_ID_MSG;
	}
}

bool Localized_String_Map::copy_from_file(const std::string &file_path)
{
	bool good = false;
	std::ifstream ifs (file_path);
	if (ifs.good())
	{
		this->language_id.clear();
		this->strings.clear();
		
		ifs >> *this;
		good = true;
	}
	else
	{
		LOG_NORMAL("Uninitialized localized strings set! Could not open file: %s", file_path.c_str());
	}
	ifs.close();

	return good;
}

std::istream& operator>>(std::istream& is, cdx::Localized_String_Map& ls)
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

std::ostream& operator<<(std::ostream& os, cdx::Localized_String_Map& ls)
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

Localizer* Localizer::current = nullptr;

void Localizer::add_language(cdx::Localized_String_Map& lsm)
{
	all_languages[lsm.get_language_id()] = lsm;
}

void Localizer::add_language(cdx::Localized_String_Map&& lsm)
{
	all_languages[lsm.get_language_id()] = std::move(lsm);
}

Localized_String_Map* Localizer::get_language(const std::string& lang_id)
{
	auto it = all_languages.find(lang_id);
	if (it != all_languages.end())
	{
		return &all_languages[lang_id];
	}
	LOG_NORMAL("Language identifier unknown! Nullptr is returned for language=\"%s\".", lang_id.c_str());
	return nullptr;
}

bool Localizer::has_language(const std::string& lang_id) const
{
	auto it = all_languages.find(lang_id);
	return it != all_languages.end();
}

bool Localizer::set_default_language(const std::string &lang_id)
{
	for (auto& it : all_languages)
	{
		if (it.first == lang_id)
		{
			default_language = &it.second;
			return true;
		}
	}
	return false;
}

bool Localizer::set_fallback_language(const std::string &lang_id)
{
	for (auto& it : all_languages)
	{
		if (it.first == lang_id)
		{
			fallback_language = &it.second;
			return true;
		}
	}
	return false;
}

const char* Localizer::get_str_from_default_language(const int n) const
{
	const char* str = Localized_String_Map::NO_STRING_FOR_ID_MSG;

	if (default_language)
	{
		str = default_language->get_str(n);

		if (str != Localized_String_Map::NO_STRING_FOR_ID_MSG) // (lazy comparison allowed due to constant)
		{
			return str;
		}
	}
	if (fallback_language)
	{
		str = fallback_language->get_str(n);

		if (str != Localized_String_Map::NO_STRING_FOR_ID_MSG) // (lazy comparison allowed due to constant)
		{
			return str;
		}
	}

	LOG_NORMAL("No localized string with id=%i for default and fallback language found!", n);
	return str;
}

const char* Localizer::get_str(const int n)
{
	return current->get_str_from_default_language(n);
}
