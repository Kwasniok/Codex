//
//  configuration.cpp
//  Codex
//
//  Created by Jens Kwasniok on 23.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "configuration.h"

using namespace cdx;

bool Configuration::is_valid_key(const std::string& key)
{
	return  (key.length() > 0) && (key.find(' ') == std::string::npos);
}

bool Configuration::set_bool(const std::string& key, bool val)
{
	if (is_valid_key(key))
	{
		val_bool[key] = val;
		return true;
	}
	return false;
}
bool Configuration::set_long(const std::string& key, long val)
{
	if (is_valid_key(key))
	{
		val_long[key] = val;
		return true;
	}
	return false;
}
bool Configuration::set_double(const std::string& key, double val)
{
	if (is_valid_key(key))
	{
		val_double[key] = val;
		return true;
	}
	return false;
}
bool Configuration::set_string_utf8(const std::string& key, const String_UTF8& val)
{
	if (is_valid_key(key))
	{
		val_string_utf8[key] = val;
		return true;
	}
	return false;
}

bool Configuration::has_bool(const std::string& key)
{
	auto it = val_bool.find(key);
	return it != val_bool.end();
}
bool Configuration::has_long(const std::string& key)
{
	auto it = val_long.find(key);
	return it != val_long.end();
}
bool Configuration::has_double(const std::string& key)
{
	auto it = val_double.find(key);
	return it != val_double.end();
}
bool Configuration::has_string_utf8(const std::string& key)
{
	auto it = val_string_utf8.find(key);
	return it != val_string_utf8.end();
}

bool Configuration::get_bool(const std::string& key)
{
	return val_bool[key];
}
long Configuration::get_long(const std::string& key)
{
	return val_long[key];
}
double Configuration::get_double(const std::string& key)
{
	return val_double[key];
}
String_UTF8 Configuration::get_string_utf8(const std::string& key)
{
	return val_string_utf8[key];
}

std::ostream& operator<<(std::ostream& os, Configuration& config)
{
	os << "UTF8" << std::endl;
	os << "CODEX_CONFIG" << std::endl << std::endl;

	std::pair<const char*, const char*> tag;

	for (auto& p : config.get_all_bool_values())
	{
		os << "bool" << ':' << p.first << '=' << (p.second ? "true" : "false") << ';' << std::endl;
	}
	for (auto& p : config.get_all_long_values())
	{
		os << "long" << ':' << p.first << '=' << p.second << ';' << std::endl;
	}
	for (auto& p : config.get_all_double_values())
	{
		os << "double" << ':' << p.first << '=' << p.second << ';' << std::endl;
	}
	for (auto& p : config.get_all_string_utf8_values())
	{
		os << "string_utf8" << ':' << p.first << '=' << p.second << ';' << std::endl;
	}

	return os;
}
std::istream& operator>>(std::istream& is, Configuration& config)
{
	Configuration tmp;
	std::string line;
	std::string type, key, value;

	std::getline(is, line);
	if (line != "UTF8") {is.setf(std::ios_base::failbit); return is;}
	std::getline(is, line);
	if (line != "CODEX_CONFIG") {is.setf(std::ios_base::failbit); return is;}

	while (is.good() && std::getline(is, line))
	{
		std::istringstream line_stream {line};

		if (line.length() == 0) continue;
		if (line[0] == '#') continue;

		line_stream >> std::ws;
		if (std::getline(line_stream, type, ':') &&
			std::getline(line_stream, key, '=') &&
			std::getline(line_stream, value, ';')
			)
		{
			line_stream >> std::ws;

			if (!line_stream.eof())
			{
				LOG_NORMAL("[Config] Could not add value of type '%s' and with name '%s' "
						   "from instream because of an unexpected character after ';'.",
						   type.c_str(), key.c_str());
				continue;
			}

			if (!Configuration::is_valid_key(key))
			{
				is.setf(std::ios_base::failbit); // parse error
				LOG_NORMAL("[Config] Could not add value from instream "
						   "because '%s' is not a valid key name.", key.c_str());
				continue;
			}

			if (type == "bool")
			{
				if (value == "true") tmp.set_bool(key, true);
				else if (value == "false") tmp.set_bool(key, false);
				else
				{
					is.setf(std::ios_base::failbit); // parse error
					LOG_NORMAL("[Config] Could not add value of type '%s' and with name '%s' "
							   "from instream because '%s' is not a valid value of that type.",
							   type.c_str(), key.c_str(), value.c_str());
				}
				continue;
			}

			std::istringstream value_stream {value};

			if (type == "long")
			{
				long l;
				value_stream >> l; // only valid if all characters were read
				if (!value_stream.fail() && value_stream.eof()) tmp.set_long(key, l);
				else
				{
					is.setf(std::ios_base::failbit); // parse error
					LOG_NORMAL("[Config] Could not add value of type '%s' and with name '%s' "
							   "from instream because '%s' is not a valid value of that type.",
							   type.c_str(), key.c_str(), value.c_str());
				}
				continue;
			}
			if (type == "double")
			{
				double d;
				value_stream >> d; // only valid if all characters were read
				if (!value_stream.fail() && value_stream.eof()) tmp.set_double(key, d);
				else
				{
					is.setf(std::ios_base::failbit); // parse error
					LOG_NORMAL("[Config] Could not add value of type '%s' and with name '%s' "
							   "from instream because '%s' is not a valid value of that type.",
							   type.c_str(), key.c_str(), value.c_str());
				}
				continue;
			}
			if (type == "string_utf8")
			{
				tmp.set_string_utf8(key, {value});
				continue;
			}
		}
		else
		{
			// parse error
			is.setf(std::ios_base::failbit);
		}
	}

	config = std::move(tmp);

	return is;
}

