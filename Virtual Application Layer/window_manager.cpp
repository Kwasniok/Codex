//
//  window_manager.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "window_manager.h"

using namespace val;

Window_Manager* Window_Manager::win_manager = nullptr;

Window_Manager::~Window_Manager()
{
	
}

bool Window_Manager::initialize()
{
	return true;
}

void Window_Manager::destroy()
{
	for (Window* win : windows) {
		destroy_window(win);
	}

	windows.clear();
}

void Window_Manager::add_window_to_list(val::Window *win)
{
	if (!has_window(win))
	{
		windows.push_back(win);
#if VAL_DEBUG_WINDOW_LIST
		LOG_DEBUG("Added to window list:     <%p>", win);
#endif
	}
	else
	{
#if VAL_DEBUG_WINDOW_LIST
		LOG_DEBUG("Double entry denied:      <%p>", win);
#endif
	}
}

void Window_Manager::remove_window_from_list(val::Window *win)
{
	auto it = find(windows.begin(), windows.end(), win);
	if (it != windows.end())
	{
		windows.erase(it);
#if VAL_DEBUG_WINDOW_LIST
		LOG_DEBUG("Removed from window list: <%p>", win);
#endif
	}
}

bool Window_Manager::has_window(val::Window *win)
{
	auto it = find(windows.begin(), windows.end(), win);
	return it != windows.end();
}