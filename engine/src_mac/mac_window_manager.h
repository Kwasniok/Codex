//
//  mac_window_manager.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_window_manager__
#define __Codex__mac_window_manager__

#include "window_manager.h"
#include "CDXWindowDelegate.h"
#include "mac_window.h"

namespace cdx {

	class Window_Manager_Mac : public Window_Manager {
		CDXWindowDelegate* delegate = NULL;

	public:
		virtual bool initialize();
		virtual ~Window_Manager_Mac();
		
		virtual Window* create_window(const cdx::Rect& bounds,
									  const std::string title,
									  bool closable,
									  bool resizable,
									  bool borderless);
		virtual void destroy_window(Window* win);
	};

}

#endif /* defined(__Codex__mac_window_manager__) */
