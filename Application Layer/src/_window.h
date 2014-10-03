//
//  _window.h
//  Portable Game Test
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Portable_Game_Test__window_h
#define Portable_Game_Test__window_h

#include "window.h"

namespace application_layer {

	//! initializes erverything necessary to be able to create windows
	//! @return true if successfully initialized all things needed to be able to create windows
	//! @see _destroy_windows()
	bool _initialize_windows();
	//! destroys all windows which weren't destroyed manually and releases all resources initialized
	//! in _initialize_windows()
	//! @see _initialize_windows()
	void _destroy_windows();

	//! returns a vector containing all created but yet not destroyed windows
	//! @return all created windows
	//! @see _add_window_reference_to_list(Window* win), _remove_window_reference_from_list(Window* win)
	inline std::vector<Window*> _get_window_list();
	//! adds the reference to a window to the window list. This window will now be destroyed
	//! automatically inside the terminate routine.
	//! @see _remove_window_reference_from_list(Window* win), _get_window_list()
	inline void _add_window_reference_to_list(Window* win);
	//! removes the reference to the window. This window will no longer be destroyed automatically
	//! inside the terminate routine!
	//! @see _add_window_reference_to_list(Window* win), _get_window_list()
	inline void _remove_window_reference_from_list(Window* win);

	//! @see _initialize_windows();
	bool _platform_initialize_windows();
	//! @see _destroy_windows();
	void _platform_destroy_windows();
}

#endif
