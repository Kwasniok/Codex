//
//  localized_strings.cpp
//  Codex
//
//  Created by Jens Kwasniok on 20.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "localized_strings.h"

using namespace cdx;

const String_UTF8& Localized_String_Map::NO_STRING_FOR_ID_MSG
	= String_UTF8("~NO LOCALIZED STRING~");

void Localized_String_Map::set_str(const String_UTF8& id, const String_UTF8& str)
{
	std::pair<String_UTF8, String_UTF8> isp = {id, str};
	set_str(isp);
}

void Localized_String_Map::set_str(std::pair<String_UTF8, String_UTF8>& isp)
{
	auto it = strings.find(isp.first);
	if (it != strings.end())
	{
		LOG_NORMAL("Redefinition of a loalized string for language=%s and id=%s.",
				   language_id.c_str(), isp.first.c_str());
	}

#ifdef DEBUG
	if(!isp.second.good())
	{
		LOG_DEBUG("Found string with bad UTF-8 format for language=%s and id=%s: \n\t\"%s\"",
				  language_id.c_str(), isp.first.c_str(), isp.second.c_str());
	}
#endif

	strings[isp.first] = isp.second;
}

const String_UTF8& Localized_String_Map::get_str(const String_UTF8& id) const
{
	auto it = strings.find(id);
	if (it != strings.end())
	{
		return it->second;
	}
	else
	{
		return NO_STRING_FOR_ID_MSG;
	}
}

bool Localized_String_Map::remove_str(const String_UTF8& id)
{
	auto it = strings.find(id);
	if (it != strings.end())
	{
		strings.erase(it);
		return true;
	}
	return false;
}

void Localized_String_Map::set_language_id(const cdx::String_UTF8& lang_id)
{
#ifdef DEBUG
	if (!lang_id.good())
	{
		LOG_DEBUG("Found string with bad format UTF-8 format for language=%s.",
				  lang_id.c_str());
	}
#endif

	language_id = lang_id;
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
		LOG_NORMAL("Uninitialized localized strings set! Could not open file: %s",
				   file_path.c_str());
	}
	ifs.close();

	return good;
}

Localizer Localizer::current;

void Localizer::add_language(cdx::Localized_String_Map& lsm)
{
	all_languages[lsm.get_language_id()] = lsm;
}

void Localizer::add_language(cdx::Localized_String_Map&& lsm)
{
	all_languages[lsm.get_language_id()] = std::move(lsm);
}

bool Localizer::remove_language(const String_UTF8& lang_id)
{
	auto it = all_languages.find(lang_id);
	if (it != all_languages.end()) // language defined?
	{
		Localized_String_Map* rm = &it->second;
		if (rm == default_language) default_language = nullptr;
		if (rm == fallback_language) fallback_language = nullptr;

		all_languages.erase(it);

		return true;
	}
	return false;
}

Localized_String_Map* Localizer::get_language(const String_UTF8& lang_id)
{
	auto it = all_languages.find(lang_id);
	if (it != all_languages.end())
	{
		// language defined
		return &all_languages[lang_id];
	}
	LOG_NORMAL("Language identifier unknown! Nullptr is returned for language=%s.",
			   lang_id.c_str());
	return nullptr;
}

bool Localizer::has_language(const String_UTF8& lang_id) const
{
	auto it = all_languages.find(lang_id);
	return it != all_languages.end();
}

bool Localizer::set_default_language(const String_UTF8& lang_id)
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

bool Localizer::set_fallback_language(const String_UTF8& lang_id)
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

const String_UTF8& Localizer::get_str(const String_UTF8& id) const
{
	if (default_language)
	{
		const String_UTF8& str = default_language->get_str(id);

		if (str != Localized_String_Map::NO_STRING_FOR_ID_MSG)
		{
			return str;
		}
	}
	if (fallback_language)
	{
		const String_UTF8& str = fallback_language->get_str(id);

		if (str != Localized_String_Map::NO_STRING_FOR_ID_MSG)
		{
			return str;
		}
	}

	LOG_NORMAL("Found no localized string with id=%s for default and fallback language!", id.c_str());
	return Localized_String_Map::NO_STRING_FOR_ID_MSG;
}

void Localizer::clear()
{
	default_language = nullptr;
	fallback_language = nullptr;
	all_languages.clear();
}

std::istream& operator>>(std::istream& is, cdx::Localized_String_Map& ls)
{
	// unicode format & language identifier
	std::string s;
	is >> s;
	if (s == "UTF8")
	{
		is >> s;
	}
	else
	{
		LOG_NORMAL("Missing format signature for localization file (expected 'UTF8')!");
		is.setf(std::ios_base::failbit);
		return is;
	}
	if (!s.empty())
	{
		ls.set_language_id({s});
	}
	else
	{
		LOG_NORMAL("Missing language identifier for localization file!");
		is.setf(std::ios_base::failbit);
		return is;
	}

	// id string list:
	std::pair<String_UTF8, String_UTF8> p;
	char c = EOF;

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
		if (p.first.empty())
		{
			LOG_NORMAL("Missing string identifier in language %s!", ls.get_language_id().c_str());
			is.setf(std::ios_base::failbit);
			break;
		}
		else
		{
			ls.set_str(p);
		}
	}
	while (is.good());

	return is;
}

std::ostream& operator<<(std::ostream& os, cdx::Localized_String_Map& ls)
{
	// unicode format
	os << "UTF8" << std::endl;

	// language identifier:
	os << ls.get_language_id() << std::endl;

	// id string list:
	std::pair<String_UTF8, String_UTF8> p;
	for (auto it : ls.get_all())
	{
		p.first = it.first;
		p.second = it.second;
		os << p;
		os << ";" << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, std::pair<String_UTF8, String_UTF8>& p)
{
	std::pair<String_UTF8, String_UTF8> tmp;
	
	char c = EOF;
	is >> tmp.first;
	is >> c;
	if (c != ':')
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
	while (c = is.get(), is.good() && c != '"')
	{
		tmp.second += c;
	}
	
	if (is.good())
	{
		p = tmp;
	}
	
	return is;
}

std::ostream& operator<<(std::ostream& os, std::pair<String_UTF8, String_UTF8>& p)
{
	os << p.first << " : \"" << p.second << "\"";
	
	return os;
}
