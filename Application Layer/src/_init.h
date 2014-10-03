//
//  _init.h
//  Codex
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Codex__init_h
#define Codex__init_h

#include "init.h"
#include "_window.h"

namespace application_layer {

	bool _platform_initialize();
	void _platform_destroy();
	void _platform_poll_events();
	void _platform_wait_events();
	
}
#endif
