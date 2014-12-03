//
//  window.cpp
//  Codex
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include "_window.h"
#include <iostream>

using namespace application_layer;


// -----------
// Global Variables
// -----------

namespace application_layer {
	//! list of all created but yet not destroyed windows (do not use directly!)
	//! @see _get_window_list(), _add_window_reference_to_list(Window*), _remove_window_reference_from_list(Window*)
	std::vector<Window*> _windows;
}


// -----------
// Global Functions
// -----------

bool application_layer::_initialize_windows()
{
	return _platform_initialize_windows();
}

void application_layer::_destroy_windows()
{
	// destroy all listed windows
	for (Window* win : _get_window_list()) {
		win->destroy();
	}

	_platform_destroy_windows();
}


inline std::vector<Window*> application_layer::_get_window_list()
{
	return _windows;
}

inline void application_layer::_add_window_reference_to_list(Window* win)
{
	// prevent double entries
	if (std::find(_windows.begin(), _windows.end(), win) == _windows.end())
	{
#if _AL_DEBUG_WINDOW_LIST
		std::cout << "Added window to list:     " << win << std::endl;
#endif
		_windows.push_back(win);
	}
}
inline void application_layer::_remove_window_reference_from_list(Window* win)
{
	auto it = std::find(_windows.begin(), _windows.end(), win);
	if (it != _windows.end())
	{
		_windows.erase(it);
#if _AL_DEBUG_WINDOW_LIST
		std::cout << "Removed window from list: " << win << std::endl;
#endif
	}
}

// -----------
// Class Window
// -----------

Window::Window()
{ }

Window::~Window()
{
	destroy();
}

bool Window::create(const util::Rect& bounds, std::string title, bool closable,
					bool resizable, bool borderless)
{
	if (is_created())
		return true;

	util::Rect _bounds = bounds;
	if (_bounds.x < 0)
		_bounds.x = 0;
	if (_bounds.y < 0)
		_bounds.y = 0;
	if (_bounds.width < min_bound_size)
		_bounds.width = min_bound_size;
	if (_bounds.height < min_bound_size)
		_bounds.height = min_bound_size;

	_platform_create(_bounds, title, closable, resizable, borderless);

	if (_platform_window == nullptr) {
		return false;
	}

	_add_window_reference_to_list(this);

	return true;
}

void Window::destroy()
{
	if (!is_created()) return;

	_platform_destroy();
	_platform_window = nullptr;

	_remove_window_reference_from_list(this);
}

void Window::set_visible(bool vis)
{
	if (!is_created()) return;

	_platform_set_visible(vis);
}

bool Window::is_visible() const
{
	return is_created() && _platform_is_visible();
}

