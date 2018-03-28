//
//  window.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "window.h"

using namespace cdx;

void Window::was_resized()
{
	if (view)
		view->was_resized();
}