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
#include "VALWindow.h"

namespace val {

	class Window_Manager_Mac;

	class Window_Mac : public Window {
	private:
		friend class Window_Manager_Mac;
		VALWindow* mac_win = nullptr;

	public:
		virtual ~Window_Mac();

		virtual void close();

		virtual bool is_valid();
		virtual void set_visible(bool vis);
		virtual bool is_visible();

	private:
		void set_mac_window(VALWindow* win) {mac_win = win;}
		
	};

}

#endif /* defined(__Codex__mac_window__) */
