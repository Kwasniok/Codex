//
//  rect.h
//  Codex
//
//  Created by Jens Kwasniok on 22.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#ifndef Codex_rect_h
#define Codex_rect_h

namespace util {

	//! simple rectangle template
	template <typename T>
	class Rect_base {
	public:
		//! defines the position
		T x, y;
		//! defines the dimension
		T width, height;

		Rect_base();
		Rect_base(T x, T y, T w, T h);
	};


	//! simple rectangle defined by four integers
	typedef util::Rect_base<int> Rect;
}

template <typename T>
util::Rect_base<T>::Rect_base() : x (0), y (0), width (0), height(0)
{ }

template <typename T>
util::Rect_base<T>::Rect_base(T x, T y, T w, T h) : x (x), y (y), width (w), height(h)
{ }

#endif
