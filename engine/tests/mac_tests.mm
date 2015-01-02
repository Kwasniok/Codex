//
//  mac_tests.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "../include_mac/mac_codex_engine.h"

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

	// full application
	/*
	 Application::set(new Application_Mac());
	 Application::get()->initialize();

	 Window* win = Window_Manager::get()->create_window(util::Rect(200, 200, 200, 200),
	 "Placeholder Title", true, true, false);

	 win->set_visible(true);

	 for (int i=0; win->is_valid(); ++i) {
	 Application::get()->wait_events();
	 }

	 Window_Manager::get()->destroy_window(win);

	 Application::get()->destroy();
	 */
}
