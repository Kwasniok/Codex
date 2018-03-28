//
//  config.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef Codex_config_h
#define Codex_config_h

// -- ALLWAYS --
// GENERAL


// -- DEBUG --
#ifdef DEBUG
// MEMORY
#define CDX_ENABLE_MEMORY_STATISTICS true
#define CDX_MEM_STATS_PRINT_INFO false
#define CDX_MEM_STATS_PRINT_UNTRACKED_INFO false
// ROOT
#define CDX_DEBUG_ROOT true
// WINDOW MANAGER
#define CDX_DEBUG_WINDOW_LIST true

#endif // ifdef(DEBUG)

#endif /* defined(__Codex__config_h) */
