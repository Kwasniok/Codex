//
//  log.h
//  Codex
//
//  Created by Jens Kwasniok on 04.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__log__
#define __Codex__log__

#include "log_config.h"
#include <iostream>
#include <string>


#if ENABLE_DETAILED_LOG
#define LOG(type, format, ...) val::Log::get().log(type "(%s l.%i):\n\t" format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOG(type, format, ...) val::Log::get().log(format, ##__VA_ARGS__)
#endif // ENABLE_DETAILED_LOG

#if ENABLE_DEBUG_LOG
#define LOG_DEBUG(format, ...) LOG("Debug", format, ##__VA_ARGS__)
#define LOG_NORMAL(format, ...) LOG("Normal", format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#define LOG_NORMAL(format, ...) val::Log::get().log(format, ##__VA_ARGS__)
#endif // ENABLE_DEBUG_LOG


namespace val {
	
	class Log {
	private:
		static Log global_log;
		std::ostream* os;
		std::string prefix;
		static constexpr char const* endl = "\n";

	public:
		static Log& get() {return global_log;}
		Log(std::ostream* o) : os(o) { }
		Log(std::ostream* o, const char* pfx) : os(o), prefix(pfx) { }
		void set_ostream(std::ostream* o) {os = o;}
		void set_prefix(const char* p) {prefix = p;}
		//! FORMAT: <p>
		//! %i or %d --> (signed) integer <p>
		//! %l --> (singned) long <p>
		//! %ui or %ud --> unsigned integer <p>
		//! %ul --> unsigned long <p>
		//! %f --> float & double <p>
		//! %c --> char <p>
		//! %s --> null-terminated string <p>
		//! %p --> pointer <p>
		//! %% --> '%'
		void log(const char* format, ...);
	};
}

#endif /* defined(__Codex__log__) */
