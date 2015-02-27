//
//  window_manager.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__window_manager__
#define __Codex__window_manager__

#include "config.h"
#include "memory_statistics.h"
#include <vector>
#include <algorithm>
#include "log.h"
#include "string_utf8.h"
#include "rect.h"
#include "window.h"
#include "root.h"

namespace cdx {

	//! general window manager interface
	class Window_Manager {
	protected:
		std::vector<Window*> windows;

	public:
		virtual bool initialize() = 0;
		virtual ~Window_Manager() {clear();}

		virtual Window* create_window(const cdx::Rect& bounds,
									  const String_UTF8& title,
									  bool closable,
									  bool resizable,
									  bool borderless,
									  bool center) = 0;

		// destroy & clear are not virtual so they can be called by the 'abstract'
		// destructor which forgets its original type. (Before the destructor is called
		// the v-table pointer value is set to the v-table of Window_Manager.)
		void destroy_window(Window* win);
		void clear();

		const std::vector<Window*> get_all_windows() {return windows;}

	protected:
		void add_window_to_list(Window* win);
		void remove_window_from_list(Window* win);
		bool has_window(Window* win);
	};

}

#endif
