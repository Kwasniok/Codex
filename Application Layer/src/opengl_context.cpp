//
//  opengl_context.cpp
//  Codex
//
//  Created by Jens Kwasniok on 16.11.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "_opengl_context.h"

using namespace application_layer;

bool OpenGl_Context::create()
{
	return _platform_create();
}