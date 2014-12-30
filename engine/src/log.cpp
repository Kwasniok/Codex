//
//  log.cpp
//  Codex
//
//  Created by Jens Kwasniok on 04.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "log.h"

using namespace cdx;

Log Log::global_log(&std::cout);

void Log::log(const char * format, ...)
// 2nd SAVE! (~2 times slower than os&opertaor<<(os&,T&))
{
	// set-up position counter & variadic argument list
	size_t cur_pos = -1;
	va_list args;
	va_start(args, format);

	// helper vars
	std::ios_base::fmtflags old_flags;

	// write prefix (if necessary)
	if (!prefix.empty())
	{
		*os << prefix << ": ";
	}

	bool good = true;
	char c;
	while (good && (c = format[++cur_pos]) != '\0') {
		if (c == '%') // special character
		{
			c = format[++cur_pos];
			switch (c) {

					// (sigend) numeric
				case 'd': // falls through
				case 'i': *os << va_arg(args, signed int); break;           // %d|i      --> signed int
				case 'l': *os << va_arg(args, signed long); break;          // %l        --> signed long
				case 'f': *os << va_arg(args, double); break;               // %f        --> double
					// unsigned numeric
				case 'u':                                                   // %u...     --> unsigned ...
					switch (c = format[++cur_pos]) {
						default: *os << "%u" << c; break;                   // %u<undef> --> %u<undef>
						case '\0': *os << "%u"; good = false; break;        // %u\0      --> %u
						case 'd': // falls through
						case 'i': *os << va_arg(args, unsigned int); break; // %u(d|i)   --> unsigned int
						case 'l': *os << va_arg(args, unsigned long);       // %ul       --> unsigend long
					}
					break;

					// character (sequence)
				case 'c': *os << (char) va_arg(args, int); break;           // %c        --> char
				case 's': *os << (const char*) va_arg(args, size_t); break; // %s        --> string

					// special
				default:  *os << '%' << c; break;                           // %<undef>  --> %<undef>
				case '\0': *os << '%'; good = false; break;                 // %\0       --> %
				case '%': *os << '%'; break;                                // %%        --> %
				case 'p':
					old_flags = os->flags();
					os->setf(std::ios::hex, std::ios::basefield);
					*os << "<0x" << va_arg(args, size_t) << '>';            // %p        --> pointer address
					os->flags(old_flags);
					break;

			}
		}
		else // generic character
		{
			os->put(c); // faser than "*_out << c;" due to no flush
		}
	}

	va_end(args);

	*os << endl; // flushes!
}

/* 1st NOT SAFE! (~5 times slower than os&opertaor<<(os&,T&))
 {
	int return_value = -1;
	constexpr size_t buffer_size = 2048;
	static char buffer[buffer_size] = {'\0'};  // TODO: NOT SAVE!!
	va_list args;

	va_start(args, format);
	return_value = vsprintf(buffer, format, args);
	va_end(args);

	if (!prefix.empty())
	{
		*_out << prefix << ": ";
	}
	*_out << buffer << endl;

	ASSERTION_SLOW(return_value < buffer_size, "Memory curruption! Buffer is too small for expression.");
}
*/

