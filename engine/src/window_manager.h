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
#include <vector>
#include <string>
#include <algorithm>
#include "rect.h"
#include "window.h"
#include "log.h"

namespace cdx {

	class Application;
	class Window;

	//! general window manager interface
	class Window_Manager {
	protected:
		static Window_Manager* win_manager;
		std::vector<Window*> windows;

	public:
		virtual ~Window_Manager();
		static Window_Manager* get() {return win_manager;}
		static void set(Window_Manager* man) {win_manager = man;}
		
		virtual bool initialize();
		virtual void destroy();

		virtual Window* create_window(const cdx::Rect& bounds,
									  std::string title,
									  bool closable,
									  bool resizable,
									  bool borderless) = 0;
		virtual void destroy_window(Window* win) = 0;

	protected:
		void add_window_to_list(Window* win);
		void remove_window_from_list(Window* win);
		bool has_window(Window* win);
	};

}

#endif
