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
	// TODO: CHECK FOR MULTIPLE ENTRIES
	windows.push_back(win);

	std::cout << "Added to window list:     " << win << std::endl;
}

void Window_Manager::remove_window_from_list(val::Window *win)
{
	auto it = find(windows.begin(), windows.end(), win);
	if (it != windows.end())
	{
		windows.erase(it);
		std::cout << "Removed from window list: " << win << std::endl;
	}
}