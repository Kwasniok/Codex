//
//  CDXApplication.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "CDXApplication.h"

using namespace cdx;

@implementation CDXApplication


- (void)sendEvent:(NSEvent *)event
{
	#if CDX_DEBUG_MAC_PRINT_APPLICATION_EVENTS
	LOG_DEBUG("CDXApplication %p event: %s", self, event.description.UTF8String);
	#endif
	[super sendEvent:event];
}

@end
