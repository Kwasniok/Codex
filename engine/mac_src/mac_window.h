//
//  mac_window.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_window__
#define __Codex__mac_window__

#include "window.h"
#include "CDXWindow.h"
#include "mac_gl_view.h"

namespace cdx {

	class Window_Manager_Mac;

	//! based on GLFW (3.1)
	class Window_Mac : public Window {
	private:
		CDXWindow* mac_win = nil;

		// renewed from Window (see window.h)
		friend class Window_Manager_Mac;
		Window_Mac() = default;
	public:
		virtual ~Window_Mac();
		virtual bool is_valid();

		virtual void close();
		virtual void set_visible(bool vis);
		virtual bool is_visible();
		virtual void set_view(View* v);

	private:
		void set_mac_window(CDXWindow* win) {mac_win = win;}
		inline bool _is_valid() {return mac_win != nil;}
		
	};

}

#endif /* defined(__Codex__mac_window__) */
