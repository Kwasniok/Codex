//
//  mac_tests.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "../include_mac/mac_codex_engine.h"

using namespace cdx;

int main(int argc, const char * argv[])
{
	// logging
	/*
	 LOG_DEBUG("hello");
	 LOG_NORMAL("world!");
	 LOG_DEBUG_FORCE_DETAILED("hello");
	 LOG_NORMAL_FORCE_DETAILED("world!");
	 */


	// localization 1 (functionality test)
	/*
	Localized_String_Map lsm1;

		// test (re)load behaviour
	lsm1.copy_from_file(std::string("res_test/lang/TE_fb.lang.txt"));
	std::cout << lsm1 << "∑ = " << lsm1.get_all().size() << std::endl << std::endl;
	lsm1.copy_from_file(std::string("res_test/lang/TE_st.lang.txt")); // should overwrite all
	std::cout << lsm1 << "∑ = " << lsm1.get_all().size() << std::endl << std::endl;

		// test default & fallback language
	Localizer& l = Localizer::get();
	Localized_String_Map lsm2;
	lsm2.copy_from_file(std::string("res_test/lang/TE_fb.lang.txt"));
	l.add_language(lsm1); // copy
	l.add_language(std::move(lsm2)); // move
	l.set_default_language(std::string("TE_st"));
	l.set_fallback_language(std::string("TE_fb"));

	std::cout << l.get_str(1) << std::endl; // should be in default language
	std::cout << l.get_str(3) << std::endl << std::endl; // should be in fallback language

	l.remove_language(std::string("TE_st"));
	std::cout << l.get_str(1) << std::endl << std::endl; // should be in fallback language

	l.remove_language(std::string("TE_fb"));
	std::cout << l.get_str(1) << std::endl << std::endl; // should be an error string

	std::cout << l.has_language(std::string("TE_st")) << ", ";
	std::cout << l.has_language(std::string("TE_fb")) << std::endl << std::endl; // 2x false
	 */

	// localization 2 (speed test)
	/*
	constexpr long reps = 100000000;
	std::chrono::high_resolution_clock::time_point start, stop;

	int Ac, Bc;

	const String_UTF8& B1 = String_UTF8("~nullstr~");
	const String_UTF8 B1_ = B1;
	std::string B2 = std::string("some text");
	start = std::chrono::high_resolution_clock::now();
	for (long l=0; l < reps; ++l)
	{
		if (B1 == B1_) ++Bc;
	}
	stop = std::chrono::high_resolution_clock::now();

	std::cout << "Time for B: "
	<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms." << std::endl;

	const char* A1 = "~nullstr~";
	const char* A1_ = A1;
	std::string A2 = std::string("some text");
	start = std::chrono::high_resolution_clock::now();
	for (long l=0; l < reps; ++l)
	{
		if (A1 == A1_) ++Ac;
	}
	stop = std::chrono::high_resolution_clock::now();

	std::cout << "Time for A: "
	<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms." << std::endl;

	Localized_String_Map lsm;
	lsm.copy_from_file(std::string("res_test/lang/TE_fb.lang.txt"));
	Localizer& lo = Localizer::get();
	lo.add_language(lsm);
	lo.set_default_language(std::string("TE_fb"));

	start = std::chrono::high_resolution_clock::now();
	for (long l=0; l < reps; ++l)
	{
		lo.get_str(1);
	}
	stop = std::chrono::high_resolution_clock::now();

	std::cout << "Time for C: "
	<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
	<< "ms." << std::endl;
	 */


	// full application
	/*
	 Application::set(new Application_Mac());
	 Application::get()->initialize();

	 Window* win = Window_Manager::get()->create_window(util::Rect(200, 200, 200, 200),
	 "Placeholder Title", true, true, false);

	 win->set_visible(true);

	 for (int i=0; win->is_valid(); ++i) {
	 Application::get()->wait_events();
	 }

	 Window_Manager::get()->destroy_window(win);

	 Application::get()->destroy();
	 */
}
