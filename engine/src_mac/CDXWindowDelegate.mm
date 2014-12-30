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

#if CDX_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		LOG_DEBUG("CDXWindowDelegate <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	LOG_DEBUG("CDXWindowDelegate <%p> dealloc", self);
	[super dealloc];
}
#endif // CDX_DEBUG_MAC_MEM_MANGEMENT

@end