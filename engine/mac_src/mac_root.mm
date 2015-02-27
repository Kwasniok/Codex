//
//  mac_root.mm
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "mac_root.h"
#include "mac_application.h"
#include "mac_window_manager.h"

using namespace cdx;

NSAutoreleasePool* autorelease_pool = nil; //do NOT change the name (used as extern in 'mac_application.h')


bool Root_Mac::initialize()
{
	if (!can_initialize) return false;
	can_initialize = false;
	root = this;
	initialized = true; // must be true for destructor

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT_MAC] starting initialization ...");
#endif

	autorelease_pool = [[NSAutoreleasePool alloc] init];
	
#if CDX_DEBUG_ROOT
		LOG_DEBUG("[ROOT_MAC] initialized autorelease pool");
#endif

	if (!CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl")))
	{
		LOG_NORMAL("[ROOT_MAC] could not find OpenGL library");
		this->~Root_Mac();
		return false;
	}
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT_MAC] found openGL library");
#endif

	if(!configuration.copy_from_file({"res/config/default.config.txt"}))
	{
		LOG_NORMAL("[ROOT_MAC] could not load configuration");
		this->~Root_Mac();
		return false;
	}
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT_MAC] loaded configuration");
#endif

	application = NEW Application_Mac;
	if (!application->initialize())
	{
		LOG_NORMAL("[ROOT_MAC] could not initialize application");
		this->~Root_Mac();
		return false;
	}
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT_MAC] initialized application");
#endif

	window_manager = NEW Window_Manager_Mac;
	if(!window_manager->initialize())
	{
		LOG_NORMAL("[ROOT_MAC] could not initialize window manager");
		this->~Root_Mac();
		return false;
	}
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT_MAC] initialized window manager");
#endif

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT_MAC] finished initialization!");
#endif

	return true;
}

Root_Mac::~Root_Mac()
{
	if (!initialized) return;
	initialized = false;

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT_MAC] starting clean-up ...");
#endif
	if (window_manager)
	{
		delete window_manager;
		window_manager = nullptr;
#if CDX_DEBUG_ROOT
		LOG_DEBUG("[ROOT_MAC] deleted window_manager");
#endif
	}

	if (application)
	{
		delete application;
		application = nullptr;
#if CDX_DEBUG_ROOT
		LOG_DEBUG("[ROOT_MAC] deleted application");
#endif
	}

	if (autorelease_pool != nil)
	{
		[autorelease_pool drain];
		autorelease_pool = nil;
#if CDX_DEBUG_ROOT
		LOG_DEBUG("[ROOT_MAC] released autorelease pool");
#endif
	}
	root = nullptr;
	can_initialize = true;

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT_MAC] finished clean-up!");
#endif
}

void Root_Mac::perform_garbage_collection()
{
	//LOG_DEBUG("[ROOT_MAC] GC drain"); // for tests only
	[autorelease_pool drain];
	autorelease_pool = [[NSAutoreleasePool alloc] init];
}
