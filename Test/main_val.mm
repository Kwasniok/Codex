//
//  main.cpp
//  Codex
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include "log.h"
#include <iostream>
#include <fstream>
#include "assertion.h"
#include "measure.h"

#include "virtual_application_layer.h"
#include "mac_application.h"

using namespace val;

void do_f();


int i  = 1234567890;
long l = 1234567890123456;
float f = 3.141;
char c = 'g';

std::ofstream os;

void f1()
{
	for (int i=0; i<1000000; ++i)
		os << -i << ", " << -l << ", " << i << ", " << l << ", <" << &i << ">, " << f << ", " << c << std::endl;
}

void f2()
{
	for (int i=0; i<1000000; ++i)
		Log::get().log("%i, %l, %ui, %ul, %p, %f, %c", -i, -l, i, l, &i, f, c);
}

int main(int argc, const char * argv[])
{
	do_f();
    return 0;
}

void do_f()
{
	/*
	Log::get().set_prefix("BLAAA");
	Log::get().set_ostream(&os);
	std::cout << compare_time(f2, f1);
	std::cout << std::endl;
	std::cout << compare_time(f1, f2);
	*/

	/*
	localized_strings ls;
	create_localized_strings_from_file(ls, "test_lang.txt");
	//std::cout << ls;

	std::cout << ls.get_str(STRING_TEST + 100) << std::endl;
	*/

	LOG_DEBUG("hello");
	LOG_NORMAL("world!");

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
