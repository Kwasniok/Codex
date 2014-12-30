//
//  window.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__window__
#define __Codex__window__

#include "config.h"

namespace cdx {

	//! general window interface
	class Window {

	public:
		virtual ~Window();

		virtual void close() = 0;

		virtual bool is_valid() = 0;
		virtual void set_visible(bool vis) = 0;
		virtual bool is_visible() = 0;
	};

}

#endif /* defined(__Codex__window__) */
