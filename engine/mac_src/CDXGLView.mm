//
//  CDXGLView.mm
//  Codex
//
//  Created by Jens Kwasniok on 07.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "CDXGLView.h"

using namespace cdx;

@implementation CDXGLView

- (id)initWithWindow:(cdx::Window_Mac *)win
{
	self = [super init];
	if (self != nil)
	{

		mac_window = win;
		//trackingArea = nil;

		//[self updateTrackingAreas];
	}

	return self;
}
-(void)dealloc
{
	//[trackingArea autorelease];
	[super dealloc];
}

- (BOOL)isOpaque
{
	return YES;
}

- (BOOL)canBecomeKeyView
{
	return YES;
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}



/*
- (void)cursorUpdate:(NSEvent *)event
{
	setModeCursor(window, window->cursorMode);
}

- (void)mouseDown:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 GLFW_MOUSE_BUTTON_LEFT,
						 GLFW_PRESS,
						 translateFlags([event modifierFlags]));
}

- (void)mouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void)mouseUp:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 GLFW_MOUSE_BUTTON_LEFT,
						 GLFW_RELEASE,
						 translateFlags([event modifierFlags]));
}

- (void)mouseMoved:(NSEvent *)event
{
	if (window->cursorMode == GLFW_CURSOR_DISABLED)
		_glfwInputCursorMotion(window, [event deltaX], [event deltaY]);
		else
		{
			const NSRect contentRect = [window->ns.view frame];
			const NSPoint p = [event locationInWindow];

			_glfwInputCursorMotion(window, p.x, contentRect.size.height - p.y);
		}
}

- (void)rightMouseDown:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 GLFW_MOUSE_BUTTON_RIGHT,
						 GLFW_PRESS,
						 translateFlags([event modifierFlags]));
}

- (void)rightMouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void)rightMouseUp:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 GLFW_MOUSE_BUTTON_RIGHT,
						 GLFW_RELEASE,
						 translateFlags([event modifierFlags]));
}

- (void)otherMouseDown:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 (int) [event buttonNumber],
						 GLFW_PRESS,
						 translateFlags([event modifierFlags]));
}

- (void)otherMouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void)otherMouseUp:(NSEvent *)event
{
	_glfwInputMouseClick(window,
						 (int) [event buttonNumber],
						 GLFW_RELEASE,
						 translateFlags([event modifierFlags]));
}

- (void)mouseExited:(NSEvent *)event
{
	_glfwInputCursorEnter(window, GL_FALSE);
}

- (void)mouseEntered:(NSEvent *)event
{
	_glfwInputCursorEnter(window, GL_TRUE);
}

- (void)viewDidChangeBackingProperties
{
	const NSRect contentRect = [window->ns.view frame];
	const NSRect fbRect = convertRectToBacking(window, contentRect);

	_glfwInputFramebufferSize(window, fbRect.size.width, fbRect.size.height);
}

- (void)updateTrackingAreas
{
	if (trackingArea != nil)
	{
		[self removeTrackingArea:trackingArea];
		[trackingArea autorelease];
	}

	NSTrackingAreaOptions options = NSTrackingMouseEnteredAndExited |
	NSTrackingActiveInKeyWindow |
	NSTrackingCursorUpdate |
	NSTrackingInVisibleRect;

	trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
												options:options
												  owner:self
											   userInfo:nil];

	[self addTrackingArea:trackingArea];
	[super updateTrackingAreas];
}

- (void)keyDown:(NSEvent *)event
{
	const int key = translateKey([event keyCode]);
	const int mods = translateFlags([event modifierFlags]);
	_glfwInputKey(window, key, [event keyCode], GLFW_PRESS, mods);

	NSString* characters = [event characters];
	NSUInteger i, length = [characters length];

	for (i = 0;  i < length;  i++)
		_glfwInputChar(window, [characters characterAtIndex:i]);
		}

- (void)flagsChanged:(NSEvent *)event
{
	int action;
	unsigned int newModifierFlags =
	[event modifierFlags] & NSDeviceIndependentModifierFlagsMask;

	if (newModifierFlags > window->ns.modifierFlags)
		action = GLFW_PRESS;
		else
			action = GLFW_RELEASE;

			window->ns.modifierFlags = newModifierFlags;

			const int key = translateKey([event keyCode]);
			const int mods = translateFlags([event modifierFlags]);
			_glfwInputKey(window, key, [event keyCode], action, mods);
			}

- (void)keyUp:(NSEvent *)event
{
	const int key = translateKey([event keyCode]);
	const int mods = translateFlags([event modifierFlags]);
	_glfwInputKey(window, key, [event keyCode], GLFW_RELEASE, mods);
}

- (void)scrollWheel:(NSEvent *)event
{
	double deltaX, deltaY;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
	if (floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6)
	{
		deltaX = [event scrollingDeltaX];
		deltaY = [event scrollingDeltaY];

		if ([event hasPreciseScrollingDeltas])
		{
			deltaX *= 0.1;
			deltaY *= 0.1;
		}
	}
	else
#endif /*MAC_OS_X_VERSION_MAX_ALLOWED* /
	{
		deltaX = [event deltaX];
		deltaY = [event deltaY];
	}

	if (fabs(deltaX) > 0.0 || fabs(deltaY) > 0.0)
		_glfwInputScroll(window, deltaX, deltaY);
		}
*/
@end
