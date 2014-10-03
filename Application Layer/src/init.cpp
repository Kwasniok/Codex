//
//  init.cpp
//  Codex
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include "_init.h"

namespace application_layer {
	bool _initialized = false;
}

bool application_layer::initialize()
{
	if (_initialized) return true;

	if (!_platform_initialize()) {
		return false;
	}

	if (!_initialize_windows()) {
		destroy();
		return false;
	}

	_initialized = true;
	return true;
}

bool application_layer::isInitialized()
{
	return _initialized;
}

void application_layer::destroy()
{
	_destroy_windows();
	_platform_destroy();

	_initialized = false;
}

void application_layer::poll_events()
{
	_platform_poll_events();
}

void application_layer::wait_events()
{
	_platform_wait_events();
}