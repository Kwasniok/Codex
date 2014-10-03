//
//  main.cpp
//  Test
//
//  Created by Jens Kwasniok on 21.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include <iostream>
#include "applicationLayer.h"

inline void pause()
{
	std::cout << "PAUSE";
	getchar();
}

using namespace application_layer;

int main(int argc, const char * argv[]) {

	initialize();
	Window win;
	win.create(util::Rect(200, 200, 200, 200), "Placeholder Title", true, true, false);
	win.set_visible(true);

	for (int i=0; win.is_created(); ++i) {
		wait_events();
	}

	win.destroy();

	destroy();
	
    return 0;
}
