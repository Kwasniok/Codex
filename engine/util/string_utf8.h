//
//  string_utf8.h
//  Codex
//
//  Created by Jens Kwasniok on 05.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__string_utf8__
#define __Codex__string_utf8__

#include <string>

namespace cdx {

	// was not tested completely
	//! String_UTF8 is a string class completely backward-compatible to std::string.
	//! Additional functions for UTF-8 management are: add_utf8_char(), calculate_utf8_length() &
	//! good()
	class String_UTF8 : public std::string {
		typedef std::string base;

	public:
		String_UTF8() {}
		String_UTF8(const value_type* str) : base(str) { }
		String_UTF8(const base& str) : base(str) { }
		String_UTF8(const base&& str) : base(std::move(str)) { }

		//! Adds a unicode character to the string (and converts it to UTF-8).<p>
		//! operator+=() is not effected by this method!
		//! @see good(), calculate_utf8_length()
		String_UTF8& add_utf8_char(unsigned long c);
		// Storing the length is not safe! Changes inside a string are not detected.
		//! Use this method to calculate the amount of (unicode) code points in a string.<p>
		//! Warning: The (UTF-8)length is not stored and hence must be recalculated ervery time.
		//! @return amount of (unicode) code points
		base::size_type calculate_utf8_length() const;
		//! @return true if string is in correct UTF-8 format
		//! @see add_utf8_char()
		bool good() const;
	};

}

#endif /* defined(__Codex__string_utf8__) */
