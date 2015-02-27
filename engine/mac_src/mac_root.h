//
//  mac_root.h
//  Codex
//
//  Created by Jens Kwasniok on 15.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#ifndef Codex_mac_root_h
#define Codex_mac_root_h

#include "root.h"

namespace cdx {


	class Root_Mac : public Root {

	public:
		virtual bool initialize();
		virtual ~Root_Mac();
		virtual void perform_garbage_collection();
	};

}

#endif
