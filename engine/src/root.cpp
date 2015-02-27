//
//  root.cpp
//  Codex
//
//  Created by Jens Kwasniok on 22.01.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "root.h"

using namespace cdx;

Root* Root::root = nullptr;
bool Root::can_initialize = true;
Configuration Root::configuration;
Application* Root::application = nullptr;
Window_Manager* Root::window_manager = nullptr;


void Root::perform_garbage_collection()
{
	if (root)
	{
		root->_perform_garbage_collection();
	}
}
