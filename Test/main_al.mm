//
//  main2.cpp
//  Codex
//
//  Created by Jens Kwasniok on 03.12.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include <iostream>

#include "measure.h"

#include "applicationLayer.h"


using namespace application_layer;

void do_f();

int main(int argc, const char * argv[])
{
	std::cout << measure_time<std::chrono::milliseconds>(do_f) << "ms." << std::endl;
	return 0;
}

void do_f()
{

	initialize();

	Window win;
	win.create(util::Rect(200, 200, 200, 200), "Placeholder Title", true, true, false);

	win.set_visible(true);

	for (int i=0; win.is_created(); ++i) {
		wait_events();
	}

	win.destroy();

	destroy();
}
