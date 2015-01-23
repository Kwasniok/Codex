//
//  root.h
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__root__
#define __Codex__root__

#include "config.h"
#include "log.h"

namespace cdx {

	class Application;
	class Window_Manager;

	//! Root manages startup & shutdown routines and holds pointers to all (static) subsystems.<p>
	//! Only one root is allowed to be initialized. The shutdown routine will be executed when the
	//! initialized instance is destructed (e.g. goes out of scope).
	class Root {
		static bool can_initialize; // simple mutex (NOT thread-save!)
		static Application* application;
		static Window_Manager* window_manager;

		//! If true destructor is allowed to execute the shutdown routine (initialized
		//! instance only). False for all other root instances.
		bool initialized = false;

	public:
		//! initializes all subsystems (initialization routine)
		//! @return true if all subsytems were initialized correctly
		bool initialize(); // must de defined in platform specific root file
		//! destructors is shutdown rountine
		~Root(); // must de defined in platform specific root file

		static Application& get_application() {return *application;}
		static Window_Manager& get_window_manager() {return *window_manager;};
	};

}

#endif /* defined(__Codex__root__) */
