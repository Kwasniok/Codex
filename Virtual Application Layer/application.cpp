//
//  application.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "application.h"

using namespace val;

Application* Application::application = nullptr;

bool Application::set(Application *app)
{
	if (!application) {
		application = app;
		return true;
	}

	return false;
}

bool Application::initialize()
{
	return true;
}

void Application::destroy()
{
	Window_Manager::get()->destroy();
	Window_Manager::set(nullptr);

}