//
//  log.h
//  Codex
//
//  Created by Jens Kwasniok on 04.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__log__
#define __Codex__log__

#include <iostream>
#include <string>

namespace val {

	// for approach 2
	typedef int Log_Type_t;
	enum Log_Type : Log_Type_t {
		NONE    = 0x00,
		ALL     =~0x00,
		// attributes:
	    DBUG    = 0x01, // missing 'E' is intended to avoid a conflict with the macro "DEBUG"
		INFO    = 0x02, // INFO, WARING & ERROR are meant to be exclusive
		WARNING = 0x04,
		ERROR   = 0x08,
		// categories:
		MEM     = 0x10, // combine attribute(s) and cateory with or: DBUG | INFO | MEM
	};
	
	class Log { // TODO: MAKE MORE EFFICIENT: AVOID UNNECESSARY EVALUATION!
	private:
		// approach 1:
		static std::ostream* _out;
		// approach 2:
		static std::string prefix;
		static Log_Type filter;

	public:
		// approach 1:
		static Log out;
		static void set_ostream(std::ostream* o) {_out = o;}

		template <class T>
		Log& operator<<(T& x)
		{
			*_out << x;
			return *this;
		}

		// approach 2:
		static int log(Log_Type p, const char* format, ...) __printflike(2, 3);
		static void set_log_type_as_filter(Log_Type lt);
		static void add_log_type_to_filter(Log_Type lt);
		static void remove_log_type_from_filter(Log_Type lt);
		static void set_prefix(std::string& p);
	};

	constexpr char const* endl = "\n";
}

inline val::Log_Type operator&(val::Log_Type lhs, val::Log_Type rhs);
inline val::Log_Type operator|(val::Log_Type lhs, val::Log_Type rhs);
inline val::Log_Type operator~(val::Log_Type rhs);

#endif /* defined(__Codex__log__) */
