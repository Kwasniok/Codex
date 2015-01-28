//
//  configuration.h
//  Codex
//
//  Created by Jens Kwasniok on 23.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__configuration__
#define __Codex__configuration__

#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "io_pair.h"
#include <string>
#include "../util/string_utf8.h"
#include "log.h"

namespace cdx {

	class Configuration { // TODO: add static configuration options!?
		// static configurations
		// e.g. int default_window_size; ...

		// dynamic configurations
		std::map<std::string, bool> val_bool;
		std::map<std::string, long> val_long;
		std::map<std::string, double> val_double;
		std::map<std::string, String_UTF8> val_string_utf8;

	public:
		//! a key name must not contain a space character
		static bool is_valid_key(const std::string& key);

		bool set_bool(const std::string& key, bool val);
		bool set_long(const std::string& key, long val);
		bool set_double(const std::string& key, double val);
		bool set_string_utf8(const std::string& key, const String_UTF8& val);

		bool has_bool(const std::string& key);
		bool has_long(const std::string& key);
		bool has_double(const std::string& key);
		bool has_string_utf8(const std::string& key);

		bool get_bool(const std::string& key);
		long get_long(const std::string& key);
		double get_double(const std::string& key);
		String_UTF8 get_string_utf8(const std::string& key);

		const std::map<std::string, bool>& get_all_bool_values() {return val_bool;}
		const std::map<std::string, long>& get_all_long_values() {return val_long;}
		const std::map<std::string, double>& get_all_double_values() {return val_double;}
		const std::map<std::string, String_UTF8>& get_all_string_utf8_values() {return val_string_utf8;}

		bool copy_from_file(const std::string& file_path);
	};

}

std::ostream& operator<<(std::ostream& os, cdx::Configuration& config);
std::istream& operator>>(std::istream& is, cdx::Configuration& config);
#endif /* defined(__Codex__configuration__) */
