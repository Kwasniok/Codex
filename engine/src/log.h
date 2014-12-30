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

// -- MACROS --
// Synopsis:
// LOG_NORMAL(const char* format, ...)
// LOG_NORMAL_FORCE_DETAILED(const char* format, ...)
// LOG_DEBUG(const char* format, ...)
// LOG_DEBUG_FORCE_DETAILED(const char* format, ...)
//
// format := format as c-string (see cdx::Log::log for accepted formats)
// ... := argument list matching the format (otherwise the result is unpredictable)
//
// 'NORMAL' is allways activated.
// 'DEBUG' is enabled if 'ENABLE_DETAILED_LOG' is defined and true (see log_cofig.h).
// If 'ENABLE_DETAILED_LOG' is defined and true all logging messages will be extened by the
// location where they where created (file & line).
// 'FORCE_DETAILED' means THIS logging message should ALLWAYS be extended by it's location.

namespace cdx {
	
	class Log {
	private:
		static Log global_log;
		std::ostream* os;
		std::string prefix;
		static constexpr char const* endl = "\n";

	public:
		//! @return the current (global) logger
		static Log& get() {return global_log;}
		//! @param o an arbitary stream to be logged to
		Log(std::ostream* o) : os(o) { }
		//! @param o an arbitary stream to be logged to
		//! @param pfx prefix to be added before each logging message
		Log(std::ostream* o, const char* pfx) : os(o), prefix(pfx) { }
		void set_ostream(std::ostream* o) {os = o;}
		void set_prefix(const char* p) {prefix = p;}
		//! Please do not use this method directly - use the predefined macros instead. <p>
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
		//! @see LOG_NORMAL(const char* format, ...),
		//! LOG_NORMAL_FORCE_DETAILED(const char* format, ...),
		//! LOG_DEBUG(const char* format, ...),
		//! LOG_DEBUG_FORCE_DETAILED(const char* format, ...)
		void log(const char* format, ...);
	};
}

// -- MACROS (CONTINUED)

// loggging type & message only
#define L_OG_SHORT(type, format, ...) cdx::Log::get().log(type ": " format, ##__VA_ARGS__)
// + file & line
#define L_OG_DETAILED(type, format, ...) cdx::Log::get().log(type " (%s l.%i):\n\t" format, __FILE__, __LINE__, ##__VA_ARGS__)

// ENABLE_DETAILED_LOG: make detailed default
#if ENABLE_DETAILED_LOG
#define L_OG(type, format, ...) L_OG_DETAILED(type, format, ##__VA_ARGS__)
#else
#define L_OG(type, format, ...) L_OG_SHORT(type, format, ##__VA_ARGS__)
#endif // ENABLE_DETAILED_LOG

// NORMAL & NORMAL_FORCE_DETAILED mode
#define LOG_NORMAL(format, ...) L_OG("Normal", format, ##__VA_ARGS__)
#define LOG_NORMAL_FORCE_DETAILED(format, ...) L_OG_DETAILED("Normal", format, ##__VA_ARGS__)

// DEBUG & DEBUG_FORCE_DETAILED mode
#if ENABLE_DEBUG_LOG
#define LOG_DEBUG(format, ...) L_OG("Debug", format, ##__VA_ARGS__)
#define LOG_DEBUG_FORCE_DETAILED(format, ...) L_OG_DETAILED("Debug", format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#define LOG_DEBUG_FORCE_DETAILED(format, ...)
#endif // ENABLE_DEBUG_LOG

#endif /* defined(__Codex__log__) */
