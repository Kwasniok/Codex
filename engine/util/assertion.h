//
//  assertion.h
//  Codex
//
//  Created by Jens Kwasniok on 24.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_assertion_h
#define Codex_assertion_h

#include <stdlib.h>
#include <iostream>

#ifdef DISABLE_ALL_ASSERTIONS
#define ASSERTION(expr, msg)
#else
#define ASSERTION(expr, msg)\
	if (!(expr)) {\
		std::cout << "Assertion failed (" << __FILE__ << " l." << __LINE__ << "): `" << msg << "'" << std::endl;\
		abort();\
	}
#endif // DISABLE_ALL_ASSERTIONS

#ifdef DISABLE_SLOW_ASSERTIONS
#define ASSERTION_SLOW(expr, msg)
#else
#define ASSERTION_SLOW(expr, msg) ASSERTION(expr, msg)
#endif // DISABLE_SLOW_ASSERTIONS

#endif
