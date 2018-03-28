//
//  CDXGLView.h
//  Codex
//
//  Created by Jens Kwasniok on 07.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef __Codex__CDXGLView__
#define __Codex__CDXGLView__

#include "mac_config.h"
#import <AppKit/AppKit.h>
#include "log.h"

namespace cdx {
	class Window_Mac;
	class Window_Mac;
}

@interface CDXGLView : NSOpenGLView
{
	cdx::Window_Mac* mac_window;
	//NSTrackingArea* trackingArea;
}

- (instancetype)init MAC_UNAVAILABLE("this method leaks setting the window pointer");
- (instancetype)initWithWindow:(cdx::Window_Mac*)win;

@end

#endif /* defined(__Codex__CDXGLView__) */
