//
//  mac_application.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_application__
#define __Codex__mac_application__

#include "application.h"
#include "CDXApplication.h"
#include "CDXApplicationDelegate.h"
#include "mac_window_manager.h"


namespace cdx {

	class Application_Mac : public Application {
		NSAutoreleasePool* autorelease_pool = NULL;
		CDXApplicationDelegate* delegate = NULL;

	public:
		virtual bool initialize();
		virtual ~Application_Mac();

		virtual void poll_events();
		virtual void wait_events();
	};

}

#endif /* defined(__Codex__mac_application__) */
