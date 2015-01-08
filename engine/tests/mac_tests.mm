//
//  mac_tests.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "../include_mac/mac_codex_engine.h"

using namespace cdx;

// NEVER! change these classes & functions:

// print as binary
/*
static_assert(sizeof(unsigned long) == 8, "unsigned long must be 8 bytes long");
struct Binary_Word {
	unsigned long value;
	Binary_Word() { }
	Binary_Word(unsigned long l) : value(l) { }
};
std::ostream& operator<<(std::ostream& os, Binary_Word& bl);

static_assert(sizeof(unsigned char) == 1, "unsigned char must be 1 byte long");
struct Binary_Byte {
	unsigned char value;
	Binary_Byte() { }
	Binary_Byte(unsigned long l) : value(l) { }
};
std::ostream& operator<<(std::ostream& os, Binary_Byte& bb);
*/

int main(int argc, const char * argv[])
{
	// test utilities
	/*
	Binary_Word bl = 0b1010101010101010101010101010101010101010101010101010101010101010;
	std::cout << bl << std::endl;
	Binary_Byte bb = 0b10101010;
	std::cout << bb << std::endl;
	 */

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

	// localization 3 (UTF-8 strings)
	/*
	// unicode codepoint-to-character convertion
	String_UTF8 s;
	Binary_Byte bb;

	// critical
	long ls[] = {0x0, 0x7F, 0x80, 0x7FF, 0x800, 0xFFFF, 0x100000, 0x1FFFFF, 0x200000};
	// random
	//long ls[] = {0x78, 0x6F, 0x125, 0x633, 0x18F3, 0x7F85, 0x1B0C36, 0x1F90CF, 0x25A463};

	for (long l : ls)
	{
		s.add_utf8_char(l);
		std::cout <<"U+" <<  std::hex << l << " (" << std::dec << s.length() << ") : ";
		for (char c : s)
		{
			bb.value = c;
			std::cout << bb << "  ";
		}
		std::cout << std::endl;
		s.clear();
	}
	 */


	/*
	// length of bytes & writing all characters (can lag)
	String_UTF8 s;
	//std::ofstream log_file("log.txt");
	//if (!log_file.good()) abort();

	Binary_Byte bb;
	// 1 byte
	for (long l=0x00000; l < 0x200000; ++l)
	{
		s.clear();
		s.add_utf8_char(l);

		bool error;
		switch (s.length()) {
			default : error = true; break;
			case 1: if (l >= 0x000000 && l <= 0x00007F) error = false; break;
			case 2: if (l >= 0x000080 && l <= 0x0007FF) error = false; break;
			case 3: if (l >= 0x000800 && l <= 0x00FFFF) error = false; break;
			case 4: if (l >= 0x010000 && l <= 0x1FFFFF) error = false; break;
		}

		if (error) {
			std::cout <<"LENGTH ERROR @ U+" <<  std::hex << l <<
				" (" << std::dec << s.length() << ") : ";
			for (char c : s) {
				bb.value = c;
				std::cout << bb << "  ";
			}
			std::cout << std::endl;

			// set breakpoint here:
			s.add_utf8_char(l);
		}

		std::cout << s;
		//log_file << s;

	}

	//log_file.close();
	 */

	/*
	// length only
	constexpr long reps = 0xFF;
	std::cout << s.calculate_length_utf8() << std::endl;
	for (long l=0; l<reps; ++l)
	{
		s += char (l % 255);
		std::cout << std::hex << l << " : " << std::dec << s.calculate_length_utf8() << std::endl;

	}
	*/

	/*
	// format correctness
	String_UTF8 s;
		// U+000000 -> U+1FFFFF
	for (long l=0x000000; l<0x1FFFFF; ++l)
	{
		s.clear();
		s.add_utf8_char(l);
		if(!s.good())
		{
			std::cout << "error @ c= 0x" << std::hex << l <<  " : "
				<< s.good() << " (should be = " << false << ")" << std::endl;
		}
	}
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

/*
std::ostream& operator<<(std::ostream& os, Binary_Word& bl)
{
	constexpr int bits = sizeof(bl) * 8;

	int i = bits - 1;
	os << "0b";
	for ( ; i > -1; --i)
	{
		os << bool(bl.value & (1L << i));
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, Binary_Byte& bb)
{
	constexpr int bits = sizeof(bb) * 8;

	int i = bits - 1;
	os << "0b";
	for ( ; i > -1; --i)
	{
		os << bool(bb.value & (1L << i));
	}

	return os;
}
 */
