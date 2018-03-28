//
//  string_utf8.cpp
//  Codex
//
//  Created by Jens Kwasniok on 05.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "string_utf8.h"

using namespace cdx;

String_UTF8& String_UTF8::add_utf8_char(unsigned long c)
{
	if (c < 0x000080)  // is ASCII (U+00000 - U+0x0007F)
	{
		base::operator+=(c);
		return *this;
	}
	char c1 = 0xC0; // 11??????
	char c2 = 0x80; // 10??????
	if (c < 0x000800) // 2 byte UTF-8 code point (U+00080 - U+0x007FF)
	{
		c1 |= (c >>  6) & 0x1F; // 110?????
		c2 |=  c        & 0x3F; // 10??????

		base::operator+=(c1);
		base::operator+=(c2);
		return *this;
	}
	c1 = 0xE0; // 1110????
	char c3 = 0x80; // 10??????
	if (c < 0x010000) // 3 byte UTF-8 code point (U+00800 - U+0x0FFFF)
	{
		c1 |= (c >> 12) & 0x0F; // 1110????
		c2 |= (c >>  6) & 0x3F; // 10??????
		c3 |=  c        & 0x3F; // 10??????

		base::operator+=(c1);
		base::operator+=(c2);
		base::operator+=(c3);
		return *this;

	}
	c1 = 0xF0; // 1110????
	char c4 = 0x80; // 10??????
	if (c < 0x200000) // 4 byte UTF-8 code point (U+10000 - U+0x1FFFF)
	{
		c1 |= (c >> 18) & 0x07; // 11110???
		c2 |= (c >> 12) & 0x3F; // 1110????
		c3 |= (c >>  6) & 0x3F; // 10??????
		c4 |=  c        & 0x3F; // 10??????

		base::operator+=(c1);
		base::operator+=(c2);
		base::operator+=(c3);
		base::operator+=(c4);
		return *this;

	}
	// ... else error
	return *this;
}

String_UTF8::base::size_type String_UTF8::calculate_utf8_length() const
{
	// assert (good());

	base::size_type len_utf8 = 0;

	for (value_type c : *this)
	{
		// it is assumed that the string is a well-formed UTF-8 string
		// ASCII chararcters match             0x0??????? (starts with 0)
		// first unicode byte in UTF-8 matches 0x11?????? (starts with 11)
		// see : https://en.wikipedia.org/wiki/UTF-8
		// if (is ASCII || is frist utf-8 byte)
		if ((~c & 0x80) || ((c & 0xC0) == 0xC0))
		// == ((c < 0x7F) || (c > 0xC0)) if c is unsigned
		{
			++len_utf8;
		}
	}

	return len_utf8;
}

bool String_UTF8::good() const
{
	int fbs = 0;
	for (auto it=this->begin(), end=this->end(); it!=end; ++it)
	{
		if (*it == 0x00) break; // '\0' (termination)
		if (~*it & 0x80) continue; // is ASCII character (0 bytes following)
		if ((*it & 0xE0) == 0xC0) // 2 byte unicode character (1 following byte)
		{
			fbs = 1;
		}
		else if ((*it & 0xF0) == 0xE0) // 3 byte unicode character (2 following bytes)
		{
			fbs = 2;
		}
		else if ((*it & 0xF8) == 0xF0) // 4 byte unicode character (3 following bytes)
		{
			fbs = 3;
		}
		else return false;

		for (int i=0; i!=fbs; ++i)
		{
			++it;
			if ((*it & 0xC0) != 0x80) return false;
		}
	}
	return true;
}
