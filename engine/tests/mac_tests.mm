//
//  mac_tests.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "../mac_include/mac_codex_engine.h"

using namespace cdx;

// NEVER! change these classes & functions:

// print as binary

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


int main(int argc, const char * argv[])
{
	// test utilities
	/*
	{
		Binary_Word bl = 0b1010101010101010101010101010101010101010101010101010101010101010;
		std::cout << bl << std::endl;
		Binary_Byte bb = 0b10101010;
		std::cout << bb << std::endl;
	}
	 */

	// logging
	/*
	{
		LOG_DEBUG("hello");
		LOG_NORMAL("world!");
		LOG_DEBUG_FORCE_DETAILED("hello");
		LOG_NORMAL_FORCE_DETAILED("world!");
	}
	 */

	// localization 0 (basic io tests)
	/*
	{
		std::pair<cdx::String_UTF8, cdx::String_UTF8> p;
		p.first = String_UTF8("STRING_ID");
		p.second = String_UTF8("string message");
		std::cout << p << std::endl;
		
		std::cout << "Please type in the last line maunally!" << std::endl;
		std::cin >> p;
		std::cout << p << std::endl;
	}
	 */

	// localization 1 (functionality test)
	/*
	{
		Localized_String_Map lsm1;

			// test (re)load behaviour
		lsm1.copy_from_file(std::string("test_res/lang/TE_fb.lang.txt"));
		std::cout << lsm1 << "∑ = " << lsm1.get_all().size() << std::endl << std::endl;
		lsm1.copy_from_file(std::string("test_res/lang/TE_st.lang.txt")); // should overwrite all
		std::cout << lsm1 << "∑ = " << lsm1.get_all().size() << std::endl << std::endl;

			// test default & fallback language
		Localizer& l = Localizer::get();
		Localized_String_Map lsm2;
		lsm2.copy_from_file(std::string("test_res/lang/TE_fb.lang.txt"));
		l.add_language(lsm1); // copy
		l.add_language(std::move(lsm2)); // move
		
		l.set_default_language(std::string("TE_st"));
		l.set_fallback_language(std::string("TE_fb"));
		std::cout << "TE_st=" << (l.has_language(std::string("TE_st"))? "true":"false") << ", ";
		std::cout << "TE_fb=" << (l.has_language(std::string("TE_fb"))? "true":"false"); // 2x true
		std::cout << std::endl << std::endl;

		std::cout << l.get_str("TEST_1_ID") << std::endl; // should be in default language
		std::cout << l.get_str("TEST_3_ID") << std::endl << std::endl; // should be in fallback language
		
		l.remove_language(std::string("TE_st"));
		std::cout << "TE_st=" << (l.has_language(std::string("TE_st"))? "true":"false") << ", ";
		std::cout << "TE_fb=" << (l.has_language(std::string("TE_fb"))? "true":"false"); // false, true
		std::cout << std::endl << std::endl;

		std::cout << l.get_str("TEST_1_ID") << std::endl << std::endl; // should be in fallback language
		
		l.remove_language(std::string("TE_fb"));
		std::cout << "TE_st=" << (l.has_language(std::string("TE_st"))? "true":"false") << ", ";
		std::cout << "TE_fb=" << (l.has_language(std::string("TE_fb"))? "true":"false"); // 2x false
		std::cout << std::endl << std::endl;
		
		std::cout << l.get_str("TEST_1_ID") << std::endl << std::endl; // should be an error string
	}
	 */

	// localization 2 (speed test)
	/*
	{
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
		lsm.copy_from_file(std::string("test_res/lang/TE_fb.lang.txt"));
		Localizer& lo = Localizer::get();
		lo.add_language(lsm);
		lo.set_default_language(std::string("TE_fb"));

		start = std::chrono::high_resolution_clock::now();
		for (long l=0; l < reps; ++l)
		{
			lo.get_str("TEST_1_ID");
		}
		stop = std::chrono::high_resolution_clock::now();

		std::cout << "Time for C: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
		<< "ms." << std::endl;
	}
	 */

	// localization 3 (UTF-8 strings)
	/*
	{
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
			std::cout <<"U+" <<  std::hex << l << " (" << std::dec << s.length() << " bytes, " << s.calculate_utf8_length() << " chars, good=" << s.good() << ") : ";
			for (char c : s)
			{
				bb.value = c;
				std::cout << bb << "  ";
			}
			std::cout << std::endl;
			s.clear();
		}
	}
	 */

	// length of bytes & writing all characters (can lag)
	/*
	{
		String_UTF8 s;
		std::ofstream log_file("log.txt");
		if (!log_file.good()) abort();

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

			//std::cout << s;
			log_file << s;

		}
		log_file.close();
	}
	 */


	// length only
	/*
	{
		String_UTF8 s;
		constexpr long reps = 0xFF;
		std::cout << s.calculate_utf8_length() << std::endl;
		for (long l=0; l<reps; ++l)
		{
			s += char (l % 255);
			std::cout << std::hex << l << " : " << std::dec << s.calculate_utf8_length() << std::endl;

		}
	}
	 */

	// format correctness
	/*
	{
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
	}
	 */

	
	// configuration
	/*
	{
		Configuration c;

		c.set_bool({"sf"}, false);
		c.set_long({"sf"}, 1L);
		c.set_double({"sf"}, 2.0);
		c.set_string_utf8({"sf"}, {"three"});

		constexpr const char* file_path_in = "test_res/config/test_in.config.txt";
		constexpr const char* file_path_out = "test_res/config/test_out.config.txt";
		std::ofstream ofs (file_path_out);
		ofs << c << std::endl;

		Configuration c2;
		c2.copy_from_file({file_path_in}); // sf2 should fail 3x

		std::cout << c2 << std::endl;
	}
	 */

	// full application (minimal)
	/*
	{
		Root_Mac root;
		if (!root.initialize()) return EXIT_FAILURE;

		Window* win = Root::get_window_manager().create_window(cdx::Rect(200, 200, 200, 200),
															   "Placeholder Title", true, true, false, true);
		win->set_visible(true);

		while (win->is_valid())
		{
			Root_Mac::get_application().wait_events();
		}

		Root_Mac::get_window_manager().destroy_window(win);
	} // end of scope --> calls root's destructor --> calls destruction routine of subsystems
	 */
	
	// full application (blinking window)
	/*
	{
		Root_Mac root;
		if (!root.initialize()) return EXIT_FAILURE;

		Window* win = Root::get_window_manager().create_window(cdx::Rect(200, 200, 200, 200),
													   "OpenGL View Test", true, true, false, true);
		if (!win) return EXIT_FAILURE;
		win->set_visible(true);

		View_Mac_GL view;
		if (!view.initialize(win)) return EXIT_FAILURE;

		win->set_view(&view);

		Context* context = NEW Context_Mac_GL;
		Context_Config cc;
		if (!context->initialize(cc, &view)) return EXIT_FAILURE;
		view.set_context(context);

		context->make_current();

		glClearColor(0.8f, 1.0f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glSwapAPPLE();

		
		float f = 0.0f;
		while (win->is_valid())
		{
			f += 0.01f;
			if (f > 1.0f) f = 0.0f;
			glClearColor(f, 1.0f - f, f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glSwapAPPLE();
			Root::get_application().wait_events();
		}

		Root::get_window_manager().destroy_window(win);

		delete context;
	}
	 */
	
	// full application (MAC raw)
	/*
	{
		//NSAutoreleasePool* autorelease_pool = [[NSAutoreleasePool alloc] init];

		//CGEventSourceRef event_source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
		//CGEventSourceSetLocalEventsSuppressionInterval(event_source, 0.0);

		//CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));

		[CDXApplication sharedApplication];
		[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
		[NSApp finishLaunching];

		CDXApplicationDelegate* app_delegate = [[CDXApplicationDelegate alloc] init];
		[NSApp setDelegate:(id)app_delegate]; // ???

		CDXWindowDelegate* win_delegate = [[CDXWindowDelegate alloc] init];
		NSRect rect = NSMakeRect(0, 0, 200, 200);
		NSUInteger style_mask;
		NSWindow* window = [[NSWindow alloc] initWithContentRect:rect
													   styleMask:style_mask
														 backing:NSBackingStoreBuffered defer:NO];

		NSView* view = [[NSView alloc] initWithFrame:rect];
		[view setWantsBestResolutionOpenGLSurface:YES]; // >= 10.6
		[window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary]; // >= 10.6

		[window setTitle:@"Title"];
		[window setContentView:view];
		[window setDelegate:win_delegate];
		[window setAcceptsMouseMovedEvents:YES];
		[window center];
		[window setRestorable:NO]; // >= 10.6

		NSOpenGLPixelFormatAttribute pfatts[23];
		unsigned int att_count = -1;
		// 1
		pfatts[++att_count] = NSOpenGLPFADoubleBuffer;
		// 2
		pfatts[++att_count] = NSOpenGLPFAClosestPolicy;
		// 3
		pfatts[++att_count] = NSOpenGLPFAOpenGLProfile; // max >= 10.7 & major > 2
		// 4
		pfatts[++att_count] = NSOpenGLProfileVersion3_2Core; // max >= 10.7 & major > 2
		// 5 + 6
		pfatts[++att_count] = NSOpenGLPFAColorSize;
		pfatts[++att_count] = 8 * 3;
		// 7 + 8
		pfatts[++att_count] = NSOpenGLPFAAlphaSize;
		pfatts[++att_count] = 8;
		// 9 + 10
		pfatts[++att_count] = NSOpenGLPFADepthSize;
		pfatts[++att_count] = 24;
		// 11 +12
		pfatts[++att_count] = NSOpenGLPFAStencilSize;
		pfatts[++att_count] = 8;
		// 13 + 14
		pfatts[++att_count] = NSOpenGLPFAAccumSize;
		pfatts[++att_count] = 0;
		// 15 + 16
		pfatts[++att_count] = NSOpenGLPFAAuxBuffers;
		pfatts[++att_count] = 0;
		// 17
		//pfatts[++att_count] = NSOpenGLPFAStereo;
		// 18 - 21
		pfatts[++att_count] = NSOpenGLPFASampleBuffers;
		pfatts[++att_count] = 1;
		pfatts[++att_count] = NSOpenGLPFASamples;
		pfatts[++att_count] = 0;
		// 22
		pfatts[++att_count] = NSOpenGLPFANoRecovery;
		// 23 <= max_pfatts
		pfatts[++att_count] = NULL;
		NSOpenGLPixelFormat* pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:pfatts];

		NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
		[context setView:view];
		[context makeCurrentContext];

		std::cout << glGetString(GL_VERSION) << std::endl;

		[window makeKeyAndOrderFront:nil];

		glClearColor(0.0f, 0.0f, 0.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glSwapAPPLE();
		glClear(GL_COLOR_BUFFER_BIT);
		glSwapAPPLE();
	}
	 */
	
}


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
