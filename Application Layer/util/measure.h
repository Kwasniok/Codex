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

template<class P> // P := precision
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

template <class P> // P := precision
long get_assumed_uncertainty(void (*func)(void), int cycles = 5)
{
	if (cycles < 0) cycles = 0;

	long measured_times[cycles];
	double average_time = 0.0;
	double assumed_uncertainty = 0.0;

	for (int c=0; c < cycles; ++c)
	{
		measured_times[c] = measure_time<P>(func);
		average_time += measured_times[c];
	}
	average_time /= cycles;

	for (int c=0; c < cycles; ++c)
	{
		assumed_uncertainty += abs(measured_times[c] - average_time);
	}
	assumed_uncertainty /= cycles;

	return assumed_uncertainty;
}

inline long get_assumed_uncertainty_in_ms(void (*func)(void), int cycles = 5)
{
	return get_assumed_uncertainty<std::chrono::milliseconds>(func, cycles);
}

float compare_time(void (*a)(void), void (*b)(void))
{
	return static_cast<float>(measure_time_in_ms(a)) / measure_time_in_ms(b);
}

#endif
