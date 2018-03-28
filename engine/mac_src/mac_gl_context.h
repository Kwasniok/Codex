//
//  mac_gl_context.h
//  Codex
//
//  Created by Jens Kwasniok on 06.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_gl_context__
#define __Codex__mac_gl_context__

#include "context.h"
#include <AppKit/AppKit.h>
#include "mac_gl_view.h"

namespace cdx {

	//! based on GLFW (3.1)
	class Context_Mac_GL : public Context {
		NSOpenGLContext* mac_context = nil;
		NSOpenGLPixelFormat* mac_pixel_format = nil;

	public:
		virtual bool initialize(Context_Config& cc, View* v);
		virtual ~Context_Mac_GL();
		virtual bool is_valid();

		virtual void make_current();
		virtual void was_resized() { } // TODO: implement?

	private:
		inline bool _is_valid() {return mac_context != nil;}
	};

}

#endif /* defined(__Codex__mac_gl_context__) */
