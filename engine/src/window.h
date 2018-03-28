//
//  window.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__window__
#define __Codex__window__

#include "config.h"
#include "memory_statistics.h"
#include "view.h"

namespace cdx {

	class Window_Manager;

	//! general window interface
	class Window {
	protected:
		View* view;
		// Window's constructor is private except for Window_Manager to prevent creations of windows
		// outside of the window manager (must be renewed for every derived class!).
		friend class Window_Manager;
		Window() : view(nullptr) { }
	public:
		virtual ~Window() = default;
		virtual bool is_valid() = 0;

		virtual void close() = 0;
		virtual void set_visible(bool vis) = 0;
		virtual bool is_visible() = 0;
		virtual void set_view(View* vp) = 0;
		View* get_view() {return view;}

		virtual void was_resized();
	};

}

#endif /* defined(__Codex__window__) */
