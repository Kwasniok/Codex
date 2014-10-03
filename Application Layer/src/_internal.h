//
//  internal.h
//  Portable Game Test
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Portable_Game_Test_internal_h
#define Portable_Game_Test_internal_h

#include "config.h"


// -----------
//  Platfrom-Specific Libraries & Macros
// -----------

#if defined(__APPLE__) && defined(__OBJC__) // APPLE & OBJ-C
// libraries
#include <AppKit/Appkit.h>
// marocs
#define _AL_UNAVAILABLE(reason) __attribute__((unavailable(reason)))

#else // ALL OTHER
// macros
#define _AL_UNAVAILABLE(reason)

#endif


// -----------
//  Handle Configurations
// -----------

#ifndef DEBUG
	#if _AL_DEBUG_OBJC_MEM_MANGEMENT || _AL_DEBUG_WINDOW_LIST
	#warning Found enabled debug option(s) outside debug mode! Deactivate this/these option(s) in 'config.h' or enable debug mode (via defineing a 'DEBUG' macro).
	#endif
#endif // DEBUG



#endif
