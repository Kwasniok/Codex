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
#include <string>
#include <algorithm>
#include "rect.h"
#include "window.h"
#include "log.h"

namespace cdx {

	//! general window manager interface
	class Window_Manager {
	protected:
		std::vector<Window*> windows;

	public:
		virtual bool initialize() = 0;
		virtual ~Window_Manager();

		virtual void clear();
		virtual Window* create_window(const cdx::Rect& bounds,
									  std::string title,
									  bool closable,
									  bool resizable,
									  bool borderless) = 0;
		virtual void destroy_window(Window* win) = 0;

		const std::vector<Window*> get_all() {return windows;}

	protected:
		void add_window_to_list(Window* win);
		void remove_window_from_list(Window* win);
		bool has_window(Window* win);
	};

}

#endif
