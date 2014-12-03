//
//  window_manager.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_window_manager_h
#define Codex_window_manager_h

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "rect.h"
#include "window.h"

namespace val {

	class Application;
	class Window;

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

		virtual Window* create_window(const util::Rect& bounds,
									  std::string title,
									  bool closable,
									  bool resizable,
									  bool borderless) = 0;
		virtual void destroy_window(Window* win) = 0;

	protected:
		void add_window_to_list(Window* win);
		void remove_window_from_list(Window* win);
	};

}

#endif
