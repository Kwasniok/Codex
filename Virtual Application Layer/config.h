//
//  config.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_config_h
#define Codex_config_h

#ifdef DEBUG

// GENERAL
#define VAL_DEBUG_WINDOW_LIST true
#define VAL_DEBUG_MEM_MANAGEMENT true

// MAC
#define VAL_DEBUG_MAC_MEM_MANGEMENT true
#define VAL_DEBUG_MAC_PRINT_APPLICATION_EVENTS true

#define MAC_UNAVAILABLE(reason) __attribute__((unavailable(reason)))

#endif // ifdef(DEBUG)

#endif /* defined(__Codex__config_h) */
