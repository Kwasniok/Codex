//
//  mac_gl_context.mm
//  Codex
//
//  Created by Jens Kwasniok on 06.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "mac_gl_context.h"

using namespace cdx;


bool Context_Mac_GL::initialize(Context_Config& cc, View* v)
{
	// check if view is valid
	View_Mac_GL* mac_gl_view = reinterpret_cast<View_Mac_GL*>(v);
	if (!mac_gl_view || !mac_gl_view->is_valid())
	{
		LOG_NORMAL("[CXT_MAC] Could not initialize context, "
				   "because no (GL) valid view was was available!");
		return false;
	}

	// prepare context initialization
	constexpr int max_attributes = 23;
	NSOpenGLPixelFormatAttribute attributes[max_attributes] = {0};
	int attribute_count = -1;

	unsigned int color_bits = cc.red_bits + cc.green_bits + cc.blue_bits;
	if (color_bits < 15)
		color_bits = 15;

	// 1
	attributes[++attribute_count] = NSOpenGLPFADoubleBuffer;
	// 2
	attributes[++attribute_count] = NSOpenGLPFAClosestPolicy;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
	if (cc.gl_version_major > 2)
	{
		// 3
		attributes[++attribute_count] = NSOpenGLPFAOpenGLProfile;
		// 4
		attributes[++attribute_count] = NSOpenGLProfileVersion3_2Core;
	}
#endif /*MAC_OS_X_VERSION_MAX_ALLOWED*/

	// 5 + 6
	attributes[++attribute_count] = NSOpenGLPFAColorSize;
	attributes[++attribute_count] = color_bits;
	// 7 + 8
	if (cc.alpha_bits > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFAAlphaSize;
		attributes[++attribute_count] = cc.alpha_bits;
	}
	// 9 + 10
	if (cc.depth_bits > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFADepthSize;
		attributes[++attribute_count] = cc.depth_bits;
	}
	// 11 +12
	if (cc.stencil_bits > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFAStencilSize;
		attributes[++attribute_count] = cc.stencil_bits;
	}
	// 13 + 14
	if (cc.accumulated_bits > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFAAccumSize;
		attributes[++attribute_count] = cc.accumulated_bits;
	}
	// 15 + 16
	if (cc.auxiliary_buffers > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFAAuxBuffers;
		attributes[++attribute_count] = cc.auxiliary_buffers;
	}
	// 17
	if (cc.stereo)
	{
		attributes[++attribute_count] = NSOpenGLPFAStereo;
	}
	// 18 - 21
	if (cc.samples > 0)
	{
		attributes[++attribute_count] = NSOpenGLPFASampleBuffers;
		attributes[++attribute_count] = 1;
		attributes[++attribute_count] = NSOpenGLPFASamples;
		attributes[++attribute_count] = cc.samples;
	}
	// 22
	attributes[++attribute_count] = NSOpenGLPFANoRecovery;
	// 23 <= max_attributes
	attributes[++attribute_count] = NULL;


	// create pixel format
	mac_pixel_format = [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
	if (!mac_pixel_format)
	{
		LOG_NORMAL("[CXT_MAC] Could not initialize context, "
				   "because no pixel attribute format was created!");
		return false;
	}

	// create context
	mac_context = [[NSOpenGLContext alloc] initWithFormat:mac_pixel_format shareContext:nil]; // TODO: SUPPORT SHARED CONTEXT!
	if (!mac_context)
	{
		LOG_NORMAL("[CXT_MAC] Could not initialize context, "
				   "because no (GL) context was created!");
		[mac_pixel_format release];
		return false;
	}

	// link view to context
	[mac_context setView:mac_gl_view->mac_gl_view];

	return true;
}

Context_Mac_GL::~Context_Mac_GL()
{
	if (_is_valid())
	{
		[mac_context autorelease];
		mac_context = nil;
		[mac_pixel_format autorelease];
		mac_pixel_format = nil;
	}
}

bool Context_Mac_GL::is_valid()
{
	return _is_valid();
}

void Context_Mac_GL::make_current()
{
	if (!_is_valid()) return;
	
	[mac_context makeCurrentContext];
}
