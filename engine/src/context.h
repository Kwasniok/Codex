//
//  context.h
//  Codex
//
//  Created by Jens Kwasniok on 06.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__context__
#define __Codex__context__

#include "config.h"
#include <openGL/gl.h>

namespace cdx {

	class View;

	struct Context_Config {
		static constexpr unsigned int default_gl_version_major = 1;
		static constexpr unsigned int default_gl_version_minor = 0;
		static constexpr unsigned int default_red_bits = 8;
		static constexpr unsigned int default_green_bits = 8;
		static constexpr unsigned int default_blue_bits = 8;
		static constexpr unsigned int default_alpha_bits = 8;
		static constexpr unsigned int default_accumulated_bits = 0;
		static constexpr unsigned int default_depth_bits = 24;
		static constexpr unsigned int default_stencil_bits = 8;
		static constexpr unsigned int default_auxiliary_buffers = 0;
		static constexpr unsigned int default_samples = 0;
		static constexpr bool default_stereo = false;

		unsigned int gl_version_major = default_gl_version_major;
		unsigned int gl_version_minor = default_gl_version_minor;
		unsigned int red_bits = default_red_bits;
		unsigned int green_bits = default_green_bits;
		unsigned int blue_bits = default_blue_bits;
		unsigned int alpha_bits = default_alpha_bits;
		unsigned int accumulated_bits = default_accumulated_bits;
		unsigned int depth_bits = default_depth_bits;
		unsigned int stencil_bits = default_stencil_bits;
		unsigned int auxiliary_buffers = default_auxiliary_buffers;
		unsigned int samples = default_samples;
		bool stereo = default_stereo;
	};

	class Context {
	public:
		virtual bool initialize(Context_Config& cc, View* v) = 0;
		virtual ~Context() = default;
		virtual bool is_valid() = 0;

		virtual void make_current() = 0;
		virtual void was_resized() = 0;
	};

}
#endif /* defined(__Codex__context__) */
