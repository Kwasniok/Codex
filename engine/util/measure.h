//
//  measure.h
//  TestCXX
//
//  Created by Jens Kwasniok on 17.10.14.
//  Copyright (c) 2014 Kwasniok. All rights reserved.
//

#ifndef TestCXX_measure_h
#define TestCXX_measure_h

#include <chrono>
#include <math.h>

//! meassures the runtime of a void(void) function
template<class P>
long measure_time(void (*func)(void))
{
	using namespace std::chrono;

	high_resolution_clock::time_point stop, start = high_resolution_clock::now();
	func();
	stop = high_resolution_clock::now();

	return duration_cast<P>(stop - start).count();
}

inline long measure_time_in_ms(void(*func)())
{
	return measure_time<std::chrono::milliseconds>(func);
}

float compare_time(void (*a)(void), void (*b)(void))
{
	return static_cast<float>(measure_time_in_ms(a)) / measure_time_in_ms(b);
}

#endif
