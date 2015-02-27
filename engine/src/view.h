//
//  view.h
//  Codex
//
//  Created by Jens Kwasniok on 05.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__openGL_view__
#define __Codex__openGL_view__

#include "context.h"

namespace cdx {

	class Window;

	class View {
	protected:
		Context* context;

		View() : context(nullptr) { }
	public:
		virtual bool initialize(Window* win) = 0;
		virtual ~View() = default;
		virtual bool is_valid() = 0;

		virtual bool set_context(Context* c);
		virtual void was_resized();
	};

}

#endif /* defined(__Codex__openGL_view__) */
