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
		//! @see get_str(), gett_all()
		void add_str(const int n, const std::string str);
		//! adds the vlaue pair (redefinitions are allowed)
		//! @see get_str(), gett_all()
		void add_str(std::pair<int, std::string>& isp);
		//! @return localized string for id and given langauge (as a c-string to improve performance)
		//! @see add_str, get_all()
		const char* get_str(const int n) const;
		//! @return map with all localized strings
		//! @see add_str(), get_str()
		const std::map<int, std::string> get_all() const {return strings;}

		//! sets the language identifier (only once allowed)
		//! @return true if id was accepted
		//! @see get_language_id()
		bool set_language_id(const std::string& lang_id);
		//! @see get_lamguage_id()
		const std::string get_language_id() const {return language_id;}

		//! clears all information and copies all new information from file until a problem occurs
		//! @returns true if no problems occurred
		bool copy_from_file(const std::string& file_path);
	};

	//TODO: ADD REMOVE METHOD (MUST INCLUDE CHECK: IF DEFAULT/FALLBACK LANGUAGE IS REMOVED --> SET POINTER TO NULL)
	class Localizer {
		//! the current (global) localization
		static Localizer* current;

		std::map<std::string, Localized_String_Map> all_languages;
		Localized_String_Map* default_language;
		Localized_String_Map* fallback_language;

	public:
		//! use this method to (re)set the global localizer
		//! @see get()
		static void set(Localizer* l) {current = l;}
		//! @return pointer to the current global localizer
		static Localizer* get() {return current;}

		//! adds the given strings to a language
		void add_language(Localized_String_Map& lsm);
		//! adds the given strings to a language
		void add_language(Localized_String_Map&& lsm);
		//! @return a pointer to the associated string set
		//! (or nullptr if the language id is unknown)
		Localized_String_Map* get_language(const std::string& lang_id);
		//! @return true if language is known
		bool has_language(const std::string& lang_id) const;
		//! sets the default language
		//! @return true if langague is known
		bool set_default_language(const std::string& lang_id);
		//! sets the fallback language
		//! @return true if langague is known
		bool set_fallback_language(const std::string& lang_id);

		//! this function is part of a short cut to improve readability & performance
		//! @return localized string from default language
		const char* get_str_from_default_language(const int n) const;

		//! this function is a short cut to improve readability & performance
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
