//
//  mac_window.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "mac_window.h"

using namespace val;

Window_Mac::~Window_Mac()
{
	if (is_valid()) {
		close();
	}
}

void Window_Mac::close()
{
	if (mac_win){
		[mac_win close];
	}

	mac_win = NULL; //TODO: CHECK FOR LEAKS
}

bool Window_Mac::is_valid()
{
	return mac_win != NULL;
}

void Window_Mac::set_visible(bool vis)
{
	if (vis)
	{
		[mac_win makeKeyAndOrderFront:nil];
	}
	else{
		[mac_win orderOut:nil];
	}
}

bool Window_Mac::is_visible()
{
	return [mac_win isVisible];
}