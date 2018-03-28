//
//  mac_gl_view.h
//  Codex
//
//  Created by Jens Kwasniok on 06.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__mac_gl_view__
#define __Codex__mac_gl_view__

#include "view.h"
#include "CDXGLView.h"

namespace cdx {

	class Window_Mac;
	class Context_Mac_GL;

	class View_Mac_GL : public View {
		friend class Window_Mac;
		friend class Context_Mac_GL;
		CDXGLView* mac_gl_view = nil;

	public:
		virtual bool initialize(Window* win);
		virtual ~View_Mac_GL();
		virtual bool is_valid();

	private:
		inline bool _is_valid() {return mac_gl_view != nil;}
	};

}

#endif /* defined(__Codex__mac_gl_view__) */
