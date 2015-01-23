//
//  application.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__application__
#define __Codex__application__

#include "config.h"
#include "memory_statistics.h"
#include "root.h"
#include "window_manager.h"

namespace cdx {

	//! general application interface
	class Application {

	public:
		virtual bool initialize() = 0;
		virtual ~Application() { };

		virtual void poll_events() = 0;
		virtual void wait_events() = 0;
	};

}

#endif /* defined(__Codex__application__) */
