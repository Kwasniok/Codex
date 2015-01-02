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

	//TODO: EXTENED FOR UNICODE STRINGS!
	class Localized_String_Map {

		//! maps all ids to the correponding string for the givien language
		std::map<int, std::string> strings;
		//! contains the language identifier
		std::string language_id;
	public:
		// pointer value is used for lazy comparison!!
		//! unique constant to indicate a missed string
		constexpr static const char* NO_STRING_FOR_ID_MSG = "~NO LOCALIZED STRING~";

		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), get_all(), remove_str()
		void add_str(const int n, const std::string str);
		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), get_all(), remove_str()
		void add_str(std::pair<int, std::string>& isp);
		//! @return localized string for id and given langauge (as a c-string to improve performance)
		//! @see add_str, get_all(), remove_str()
		const char* get_str(const int n) const;
		//! @return true if string id was found
		//! @see add_str(), get_str(), get_all()
		bool remove_str(const int n);
		//! @return map with all localized strings
		//! @see add_str(), get_str(), remove_str()
		const std::map<int, std::string> get_all() const {return strings;}

		//! sets the language identifier (only once allowed)
		//! @see get_language_id()
		void set_language_id(const std::string& lang_id) {language_id = lang_id;}
		//! @see get_lamguage_id()
		const std::string get_language_id() const {return language_id;}
		//! @return true if language id was set
		bool has_language_id() {return !language_id.empty();}

		//! clears all information and copies all new information from file until a problem occurs
		//! @returns true if no problems occurred
		bool copy_from_file(const std::string& file_path);
	};

	class Localizer {
		//! the current (global) localizer
		static Localizer* current;

		//! stores all data
		std::map<std::string, Localized_String_Map> all_languages;

		//! used as default for all look-ups
		//! should be understandable for the user
		//! can be complete
		Localized_String_Map* default_language;
		//! is used if the default language is not defined for a specific id (or is not set at all)
		//! sould allways be complete!
		Localized_String_Map* fallback_language;

	public:
		//! use this method to (re)set the global localizer
		//! @see get()
		static void set(Localizer* l) {current = l;}
		//! @return pointer to the current global localizer
		//! @see set()
		static Localizer* get() {return current;}

		//! adds the given strings to a language via a copy
		//! @see has_language(), remove_language()
		void add_language(Localized_String_Map& lsm);
		//! adds the given strings to a language via move(!)
		//! @see has_language(), remove_language()
		void add_language(Localized_String_Map&& lsm);
		//! @return true if language was found and removed
		bool remove_language(const std::string lang_id);
		//! @return a pointer to the associated string set
		//! (or nullptr if the language id is unknown)
		Localized_String_Map* get_language(const std::string& lang_id);
		//! @return true if language is known
		//! @see add_language(), remove_language()
		bool has_language(const std::string& lang_id) const;

		//! sets the default language
		//! @return true if langague is known
		//! @see set_fallback_language()
		bool set_default_language(const std::string& lang_id);
		//! sets the fallback language which is looked up if the default language is incomplete
		//! @return true if langague is known
		//! @see set_default_language
		bool set_fallback_language(const std::string& lang_id);

		//! @return localized string from default language (or fallback language if incomplete)
		//! @see set_default_language(), set_fallback_language()
		const char* get_str_non_static(const int n) const;

		//! this function is a short cut to improve readability & performance
		//! @return localized string from global localizer and default language
		//! (or fallback language if incomplete)
		static const char* get_str(const int n);

	};

}

//! FORMAT:\nLANG_ID\nid1, string1;\nid2, string2;\n...
std::istream& operator>>(std::istream& is, cdx::Localized_String_Map& ls);
//! FORMAT:\nLANG_ID\nid1, string1;\nid2, string2;\n...
std::ostream& operator<<(std::ostream& os, cdx::Localized_String_Map&  ls);
//! FORMAT:\nid, string
std::istream& operator>>(std::istream& is, std::pair<int, std::string>& p);
//! FORMAT:\nid, string
std::ostream& operator<<(std::ostream& os, std::pair<int, std::string>& p);

#endif /* defined(__Codex__locale_string__) */
