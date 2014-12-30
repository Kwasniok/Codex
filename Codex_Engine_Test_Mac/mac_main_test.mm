//
//  main.cpp
//  Codex
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "assertion.h"
#include "measure.h"

#include "mac_codex_engine.h"

using namespace cdx;

int main(int argc, const char * argv[])
{
	// logging
	/*
	LOG_DEBUG("hello");
	LOG_NORMAL("world!");
	LOG_DEBUG_FORCE_DETAILED("hello");
	LOG_NORMAL_FORCE_DETAILED("world!");
	 */

	// localization
	/*
	localized_strings ls;
	create_localized_strings_from_file(ls, "res/lang/test_lang.txt");
	std::cout << ls << std::endl;

	std::cout << ls.get_str(STRING_TEST) << std::endl;
	 */

	// full application
	/*
	Application::set(new Application_Mac());
	Application::get()->initialize();

	Window* win = Window_Manager::get()->create_window(cdx::Rect(200, 200, 200, 200),
	"Placeholder Title", true, true, false);

	win->set_visible(true);

	for (int i=0; win->is_valid(); ++i) {
	Application::get()->wait_events();
	}

	Window_Manager::get()->destroy_window(win);

	Application::get()->destroy();
	 */
}
