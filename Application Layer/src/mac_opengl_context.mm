//
//  opengl_context.cpp
//  Codex
//
//  Created by Jens Kwasniok on 16.11.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "_opengl_context.h"

using namespace application_layer;

@interface _ALOpenGLContext : NSOpenGLContext

@end

@implementation _ALOpenGLContext

@end

bool OpenGl_Context::_platform_create()
{
	_ALOpenGLContext* context = [[_ALOpenGLContext alloc] init];

	if (!context) {
		return false;
	}

	_platform_openGL_context = context;

	return true;
}