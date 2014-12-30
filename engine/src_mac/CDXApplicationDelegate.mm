//
//  CDXApplicationDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "CDXApplicationDelegate.h"

using namespace cdx;

@implementation CDXApplicationDelegate

#if CDX_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		LOG_DEBUG("CDXApplicationDelegate <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	LOG_DEBUG("CDXApplicationDelegate <%p> dealloc", self);
	[super dealloc];
}
#endif // CDX_DEBUG_MAC_MEM_MANGEMENT

@end
