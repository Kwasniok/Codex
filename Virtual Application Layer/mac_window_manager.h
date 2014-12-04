//
//  mac_window_manager.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_window_manager__
#define __Codex__mac_window_manager__

#include "config.h"
#include "window_manager.h"
#include "VALWindowDelegate.h"
#include "mac_window.h"

namespace val {

	class Window_Manager_Mac : public Window_Manager {
		VALWindowDelegate* delegate;

	public:
		virtual ~Window_Manager_Mac();

		virtual bool initialize();
		virtual void destroy();

		virtual Window* create_window(const util::Rect& bounds,
									  std::string title,
									  bool closable,
									  bool resizable,
									  bool borderless);
		virtual void destroy_window(Window* win);
	};

}

#endif /* defined(__Codex__mac_window_manager__) */
