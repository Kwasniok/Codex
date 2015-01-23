//
//  mac_root.mm
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "root.h"
#include "mac_application.h"
#include "mac_window_manager.h"

using namespace cdx;

bool Root::initialize()
{
	if (!can_initialize) return false;
	can_initialize = false;

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT] starting initialization ...");
#endif

	Application_Mac* app = NEW Application_Mac;
	if (!app->initialize())
	{
		delete app;
		can_initialize = true;
		return false;
	}
	this->application = app;
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT] initialized application");
#endif

	Window_Manager_Mac* win_man = NEW Window_Manager_Mac;
	if(!win_man->initialize())
	{
		delete app;
		delete win_man;
		can_initialize = true;
		return false;
	}
	this->window_manager = win_man;
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT] initialized window manager");
#endif

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT] finished initialization!");
#endif

	initialized = true;
	return true;
}

Root::~Root()
{
	if (!initialized) return;
	initialized = false; // prevent double destruction

#if CDX_DEBUG_ROOT
	LOG_NORMAL("[ROOT] starting clean-up ...");
#endif
	delete window_manager;
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT] deleted window_manager");
#endif
	delete application;
#if CDX_DEBUG_ROOT
	LOG_DEBUG("[ROOT] deleted application");
	LOG_NORMAL("[ROOT] finished clean-up!");
#endif
	//can_initialize = true; // TODO: check if all subsystems are deleted entirely --> uncomment
}