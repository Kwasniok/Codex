//
//  mac_config.h
//  Codex
//
//  Created by Jens Kwasniok on 30.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_mac_config_h
#define Codex_mac_config_h

#include "config.h"

// -- ALLWAYS --
// MAC
#define MAC_UNAVAILABLE(reason) __attribute__((unavailable(reason)))


// -- DEBUG --
#ifdef DEBUG
// MAC
#define CDX_DEBUG_MAC_MEM_MANGEMENT false
#define CDX_DEBUG_MAC_PRINT_APPLICATION_EVENTS false
#define CDX_DEBUG_MAC_PRINT_WINDOW_EVENTS false

#endif // ifdef(DEBUG)

#endif
