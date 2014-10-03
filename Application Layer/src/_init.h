//
//  _init.h
//  Portable Game Test
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Portable_Game_Test__init_h
#define Portable_Game_Test__init_h

#include "init.h"
#include "_window.h"

namespace application_layer {

	bool _platform_initialize();
	void _platform_destroy();
	void _platform_poll_events();
	void _platform_wait_events();
	
}
#endif
