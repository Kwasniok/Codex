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
#include "string_utf8.h"
#include "loc_string_list.h"

namespace cdx {

	class Localized_String_Map {
		//! maps all ids to the correponding string for the givien language
		std::map<int, String_UTF8> strings;
		//! contains the language identifier
		String_UTF8 language_id;
	public:
		// used as constant: allowes internal lazy comperison via c-string pointer (not used)
		//! unique constant to indicate a missed string
		static const String_UTF8& NO_STRING_FOR_ID_MSG;

		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), get_all(), remove_str()
		void add_str(const int n, const String_UTF8& str);
		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), get_all(), remove_str()
		void add_str(std::pair<int, String_UTF8>& isp);
		//! @return localized string for id and given langauge (as a c-string to improve performance)
		//! @see add_str, get_all(), remove_str()
		const String_UTF8& get_str(const int n) const;
		//! @return true if string id was found
		//! @see add_str(), get_str(), get_all()
		bool remove_str(const int n);
		//! @return map with all localized strings
		//! @see add_str(), get_str(), remove_str()
		const std::map<int, String_UTF8> get_all() const {return strings;}

		//! sets the language identifier (only once allowed)
		//! @see get_language_id()
		void set_language_id(const String_UTF8& lang_id);
		//! @see get_lamguage_id()
		const String_UTF8& get_language_id() const {return language_id;}
		//! @return true if language id was set
		bool has_language_id() {return !language_id.empty();}

		//! clears all information and copies all new information from file until a problem occurs
		//! FORMAT(UTF-8):<p>UTF8<p>LANG_ID<p>id1, string1;<p>id2, string2;<p>...
		//! @return true if no problems occurred
		bool copy_from_file(const std::string& file_path);
	};

	class Localizer {
		//! the current (global) localizer
		static Localizer current;

		//! stores all data
		std::map<String_UTF8, Localized_String_Map> all_languages;

		//! used as default for all look-ups
		//! should be understandable for the user
		//! can be complete
		Localized_String_Map* default_language;
		//! is used if the default language is not defined for a specific id (or is not set at all)
		//! sould allways be complete!
		Localized_String_Map* fallback_language;

	public:
		//! @return reference to localizer
		static Localizer& get() {return current;}

		//! adds the given strings to a language via a copy
		//! @see has_language(), remove_language()
		void add_language(Localized_String_Map& lsm);
		//! adds the given strings to a language via move(!)
		//! @see has_language(), remove_language()
		void add_language(Localized_String_Map&& lsm);
		//! @return true if language was found and removed
		bool remove_language(const String_UTF8 lang_id);
		//! @return a pointer to the associated string set
		//! (or nullptr if the language id is unknown)
		Localized_String_Map* get_language(const String_UTF8& lang_id);
		//! @return true if language is known
		//! @see add_language(), remove_language()
		bool has_language(const String_UTF8& lang_id) const;

		//! sets the default language
		//! @return true if langague is known
		//! @see set_fallback_language()
		bool set_default_language(const String_UTF8& lang_id);
		//! sets the fallback language which is looked up if the default language is incomplete
		//! @return true if langague is known
		//! @see set_default_language
		bool set_fallback_language(const String_UTF8& lang_id);

		//! @return localized string from default language (or fallback language if incomplete)
		//! @see set_default_language(), set_fallback_language()
		const String_UTF8& get_str(const int n) const;
		//! @return all languages including their localized strings in a map
		const std::map<String_UTF8, Localized_String_Map>& get_all() const {return all_languages;}

		//! restores the initial state
		void clear();
	};

}

//! FORMAT(UTF-8):<p>UTF8<p>LANG_ID<p>id1, string1;<p>id2, string2;<p>...
std::istream& operator>>(std::istream& is, cdx::Localized_String_Map& ls);
//! FORMAT(UTF-8):<p>UTF8<p>LANG_ID<p>id1, string1;<p>id2, string2;<p>...
std::ostream& operator<<(std::ostream& os, cdx::Localized_String_Map&  ls);
//! FORMAT(UTF-8):<p>UTF8<p>id, string
std::istream& operator>>(std::istream& is, std::pair<int, cdx::String_UTF8>& p);
//! FORMAT(UTF-8):<p>UTF8<p>id, string
std::ostream& operator<<(std::ostream& os, std::pair<int, cdx::String_UTF8>& p);

#endif /* defined(__Codex__locale_string__) */
