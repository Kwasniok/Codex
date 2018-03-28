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
#include <fstream>
#include <string>
#include "log.h"
#include "configuration.h"

namespace cdx {

	class Application;
	class Window_Manager;
	

	//! Root manages startup & shutdown routines and holds pointers to all (static) subsystems.<p>
	//! Only one root is allowed to be initialized. The shutdown routine will be executed when the
	//! initialized instance is destructed (e.g. goes out of scope).
	class Root {
		// statitc
	protected:
		//! pointer to current initialized root (is nullptr if no root is initialized)
		static Root* root;
		static bool can_initialize; // simple mutex (NOT thread-save!)
		//! global configuration
		static Configuration configuration;

		// pointers to sub systems
		static Application* application;
		static Window_Manager* window_manager;

	public:
		static Configuration& get_configuration() {return configuration;}
		static Application& get_application() {return *application;}
		static Window_Manager& get_window_manager() {return *window_manager;};
		//! has no effect for non-CG environments
		static void perform_garbage_collection();

		// per instance
	protected:
		//! If true destructor is allowed to execute the shutdown routine (initialized
		//! instance only). False for all other root instances.
		bool initialized = false;

	public:
		//! initializes all subsystems (initialization routine)
		//! @return true if all subsytems were initialized correctly
		virtual bool initialize() = 0;
		//! destructors calls shutdown rountine if necessary
		virtual ~Root() = default;

	protected:
		//! optional function
		virtual void _perform_garbage_collection() { };
	};

}

#endif /* defined(__Codex__root__) */
