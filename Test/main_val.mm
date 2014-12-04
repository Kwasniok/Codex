//
//  main.cpp
//  Codex
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include <iostream>

#include "measure.h"

#include "virtualApplicationLayer.h"
#include "mac_application.h"

using namespace val;

void do_f();

int main(int argc, const char * argv[])
{
	Log::log(Log_Type::DBUG, "TIME: %li ms.", measure_time<std::chrono::milliseconds>(do_f));
    return 0;
}

void do_f()
{
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
}
