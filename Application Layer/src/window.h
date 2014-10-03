//
//  window.h
//  Portable Game Test
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Portable_Game_Test_window_h
#define Portable_Game_Test_window_h

#include "_internal.h"
#include "rect.h"
#include <vector>
#include <string>


namespace application_layer {

	//! Window is a mediator between your program and the current platform. It handles all
	//! platform-specific window actions. Before using windows you have to initialize the
	//! application layer. All windows will be destroyed when destroying the application layer.
	//! @see application_layer::initialize(), application_layer::destroy()
	class Window {
	private:
		//! points to the platform-specific window
		void* _platform_window = nullptr;

	public:
		//! initializes the handler but does not create a window
		Window();
		//! destroys the window (if created)
		~Window();

		Window(const Window& other) = delete;
		Window(Window&& other) = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) = delete;

		//! create and open a window if not created
		//! @return true if window was created
		//! @see destroy()
		bool create(const util::Rect& bounds, std::string title="", bool closable=false,
					bool resizable=false, bool borderless=false);
		//! closes and destroys the window (if created)
		//! @see create()
		void destroy();
		//! internal: Do not use inside platform layer. Use in middle layer instead.
		//! @return true while window can be used
		//! @see create(), destroy()
		bool is_created() const {return _platform_window != nullptr;}
		//! has no effect if window is not created
		//! @see is_visible()
		void set_visible(bool vis);
		//! @return ture iff window is created and visible
		//! @see set_visible(bool vis)
		bool is_visible() const;

		static constexpr unsigned int min_bound_size = 20;

	private:
		//TODO: optimize performance, when implemented all platforms: Some 'middle' functions just call their 'platform' equivalent without adding some functionality. This could be improved by implement the 'middle' function directly inside the platform file and removing the 'platform' declaration. Alternative: use inline functions.
		void _platform_create_window(const util::Rect& bounds, std::string title,
									 bool closable, bool resizable, bool borderless);
		void _platform_destroy_window();
		void _platform_window_set_visible(bool vis);
		bool _platform_is_visible() const;
	};

}

#endif
