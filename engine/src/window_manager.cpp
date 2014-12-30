//
//  window_manager.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "window_manager.h"

using namespace cdx;

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

void Window_Manager::add_window_to_list(cdx::Window *win)
{
	if (!has_window(win))
	{
		windows.push_back(win);
#if CDX_DEBUG_WINDOW_LIST
		LOG_DEBUG("Added to window list:     %p", win);
#endif
	}
	else
	{
#if CDX_DEBUG_WINDOW_LIST
		LOG_DEBUG("Double entry denied:      %p", win);
#endif
	}
}

void Window_Manager::remove_window_from_list(cdx::Window *win)
{
	auto it = find(windows.begin(), windows.end(), win);
	if (it != windows.end())
	{
		windows.erase(it);
#if CDX_DEBUG_WINDOW_LIST
		LOG_DEBUG("Removed from window list: <%p>", win);
#endif
	}
}

bool Window_Manager::has_window(cdx::Window *win)
{
	auto it = find(windows.begin(), windows.end(), win);
	return it != windows.end();
}