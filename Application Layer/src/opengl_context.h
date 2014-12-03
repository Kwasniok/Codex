//
//  opengl_context.h
//  Codex
//
//  Created by Jens Kwasniok on 16.11.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_opengl_context_h
#define Codex_opengl_context_h

#include "_internal.h"

#warning OpenGL_Context is incomplete!

namespace application_layer {

	class OpenGl_Context {
		void* _platform_openGL_context = nullptr;

	public:
		OpenGl_Context();
		~OpenGl_Context();

		bool create();
		void destroy();
		bool is_created() {return _platform_openGL_context != nullptr;}

	private:
		bool _platform_create();
		void _platform_destroy();

	};
}

#endif
