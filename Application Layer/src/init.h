//
//  init.h
//  Codex
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Codex_init_h
#define Codex_init_h

#include "_internal.h"
#include "window.h"

namespace application_layer {

	//! initializes the application layer
	//! @see destroy()
	bool initialize();
	//! destroys application layer
	//! @see initialize()
	void destroy();
	//! @return true while the application layer can be used
	//! @see initialize(), destroy()
	bool isInitialized();
	//! polls all events since last poll/wait call
	//! @see wait_events()
	void poll_events();
	//! waits for the next event and polls afterwards
	//! @see poll_events
	void wait_events();
}

#endif
