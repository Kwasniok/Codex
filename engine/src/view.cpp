//
//  view.cpp
//  Codex
//
//  Created by Jens Kwasniok on 05.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "view.h"

using namespace cdx;

bool View::set_context(Context* c)
{
	if (!c) {
		context = nullptr;
		return true;
	}

	if (context) return false;
	context = c;
	return true;
}

void View::was_resized()
{
	if (context)
		context->was_resized();
}