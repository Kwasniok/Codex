//
//  CDXWindowDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "CDXWindowDelegate.h"

using namespace cdx;

@implementation CDXWindowDelegate

-(BOOL)windowShouldClose:(id)sender
{
	CDXWindow* win = sender;
	[win windowHandler]->close();

	return TRUE;
}

-(void)windowDidResize:(NSNotification *)notification
{
	CDXWindow* win = notification.object;
	if (win)
		win.windowHandler->was_resized();
	else
		LOG_NORMAL_FORCE_DETAILED("[WMAN_MAC] Could not notify window for resize."
								  "No sender was found!");
}

@end