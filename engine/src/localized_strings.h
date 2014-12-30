//
//  localized_strings.h
//  Codex
//
//  Created by Jens Kwasniok on 20.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__locale_string__
#define __Codex__locale_string__

#include "log.h"
#include <fstream>
#include <map>
#include <string>
#include "loc_string_list.h"

namespace cdx {

	// TODO: OPTIMIZE: MAP[const char* --> std::string&] (1st time c_str is read/'translated' Result is saved in map| 2nd time translation is read from map)
	// TODO: OPTIMIZE: return const char* only
	// TODO: ADD FALLBACK FOR INCOMPLETE LOCALIZATIONS
	// TODO?: EXTEND FOR MULTIPLE LANGUAGES (VIA NEW HANDLER CLASS)?
	class localized_strings {
		//! the current (global) localization
		static localized_strings* current;

		//! maps all ids to the correponding string for the givien language
		std::map<int, std::string> strings;
		//! contains the language identifier
		std::string language_id;
	public:
		//! use this method to (re)set the global localization
		//! @see get()
		static void set(localized_strings* ls);
		//! @return pointer to the current global localization
		static localized_strings* get() {return current;}

		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), gett_all()
		void add_str(std::pair<int, std::string>& isp);
		//! @return localized string for id and given langauge
		//! @see add_str, get_all()
		std::string get_str(const int number) const;
		//! @return map with all localized strings
		//! @see add_str(), get_str()
		const std::map<int, std::string> get_all() const {return strings;}

		//! sets the language identifier (only once allowed)
		//! @return true if id was accepted
		//! @see get_language_id()
		bool set_language_id(const std::string& lang_id);
		//! @see get_lamguage_id()
		const std::string get_language_id() const {return language_id;}
	};

	bool create_localized_strings_from_file(localized_strings& ls, const std::string& file_path);

}

//! FORMAT:\nLANG_ID\nid1, string1;\nid2, string2;\n...
std::istream& operator>>(std::istream& is, cdx::localized_strings& ls);
//! FORMAT:\nLANG_ID\nid1, string1;\nid2, string2;\n...
std::ostream& operator<<(std::ostream& os, cdx::localized_strings&  ls);
//! FORMAT:\nid, string
std::istream& operator>>(std::istream& is, std::pair<int, std::string>& p);
//! FORMAT:\nid, string
std::ostream& operator<<(std::ostream& os, std::pair<int, std::string>& p);

#endif /* defined(__Codex__locale_string__) */
