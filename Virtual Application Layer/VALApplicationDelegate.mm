//
//  VALApplicationDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALApplicationDelegate.h"

@implementation VALApplicationDelegate

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		val::Log::log(val::Log_Type::MEM, "VALApplicationDelegate <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	val::Log::log(val::Log_Type::MEM, "VALApplicationDelegate <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end
