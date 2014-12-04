//
//  log.cpp
//  Codex
//
//  Created by Jens Kwasniok on 04.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "log.h"

using namespace val;

Log Log::out;
std::ostream* Log::_out = &std::cout;
std::string Log::prefix;
Log_Type Log::filter = Log_Type::ALL;

int Log::log(Log_Type lt, const char * format, ...)
{
	if ((lt & filter) == lt) {
		int return_value = -1;
		constexpr int buffer_size = 2048; // TODO: NOT SAVE!!
		static char buffer[buffer_size] = {'\0'};
		va_list args;

		va_start(args, format);
		return_value = vsprintf(buffer, format, args);
		va_end(args);

		//assert(return_value < buffer_size) // TODO: ADD ASSERT

		if (!prefix.empty())
		{
			*_out << prefix << ": ";
		}
		*_out << buffer << endl;

		return return_value;
	}

	return 0;
}

void Log::set_log_type_as_filter(val::Log_Type lt)
{
	filter = lt;
}

void Log::add_log_type_to_filter(val::Log_Type lt)
{
	filter = filter | lt;
}

void Log::remove_log_type_from_filter(val::Log_Type lt)
{
	filter = filter & ~lt;
}

void Log::set_prefix(std::string &p)
{
	prefix = p;
}

inline Log_Type operator&(Log_Type lhs, Log_Type rhs)
{
	return static_cast<Log_Type>(Log_Type_t (lhs) & Log_Type_t (rhs));
}

inline Log_Type operator|(Log_Type lhs, Log_Type rhs)
{
	return static_cast<Log_Type>(Log_Type_t (lhs) | Log_Type_t (rhs));
}

inline Log_Type operator~(Log_Type rhs)
{
	return static_cast<Log_Type>(~ Log_Type_t(rhs));
}

