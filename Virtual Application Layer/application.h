//
//  application.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__application__
#define __Codex__application__

#include "window_manager.h"

namespace val {

	class Application {
	protected:
		static Application* application;

	public:
		static bool set(Application* app);

		static Application* get() {return application;}

		virtual bool initialize();
		virtual void destroy();

		virtual void poll_events() = 0;
		virtual void wait_events() = 0;
	};

}

#endif /* defined(__Codex__application__) */
