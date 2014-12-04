//
//  VALWindowDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALWindowDelegate.h"

using namespace val;

@implementation VALWindowDelegate

-(BOOL)windowShouldClose:(id)sender
{
	VALWindow* win = sender;
	[win windowHandler]->close();

	return TRUE;
}

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		Log::log(Log_Type::MEM, "VALWindowDelegate <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	Log::log(Log_Type::MEM, "VALWindowDelegate <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end