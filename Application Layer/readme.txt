//
//  readme.txt
//  Codex
//
//  Created by Jens Kwasniok on 24.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

The application layer consists of two (sub)layers.

	1) One is the "middle" layer which mediates between your application and the platfrom-specific
	   code.

	   It includes all functions which can be used from the upper layers.

	   Files containing this code are named in the following way "x.cpp" where "x" is the name of
	   the topic ("x.h" is the corresponding header file).


	2) The other layer is called "platform" layer.

	   It contains all(!) platform-specific code. Declarations refering to this layer start with
	   "platform_". This layer is (almost) hidden for the upper layers which should never(!) call
	   or influence a "platform" function or variable directly!

	   All files of the "platform" layer are called "p_x.cpp" where "x" is the topic and "p" the
	   abbreviation of the platform (_x.h is the corresponding header). (Some files end with a ".mm"
	   instead of ".cpp" this indicates the complier to interpret the code as Objective-C++ and has
	   no other meaning.)


The file structure uses the following pattern:

	Header Files:
		Pubic headers are named     "x.h"   they contain all declarations which are part of the API
		                                    and are included in the API header called
		                                    "applicationLayer.h"
		Private headers are called  "_x.h"  they consist of all "platform" declarations which are
		                                    invisible to the API user.
	Code Files:
		"Middle" layer code files are called  "x.cpp"    they contain all the code managing the
		                                                 general functionality of the application
		                                                 layer. All "platfrom" functions are called
		                                                 whithin this code.
		"Platform" layer code files are named "p_x.cpp"  they contain all platform-specific code and
		                                                 differ from platform to platform. These are
		                                                 the only files to be edited/created when
		                                                 porting your code to another platfrom.

	("x" is the name of the topic & "p" is the abbreviation of the platform)

Other naming conventions:

	Functions & Variables:
		A leading '_' in a function or variable name means this declaration is 'hidden' inside the
		application layer. An API user must not have access to this function or variable.

		A name containing 'platform' at the beginning means this function or variable is part of the
		'platform' layer. Its implementation is inside a platform-specific file. Naturally, all of
		them are also marked as 'hidden' via a leading underscore.


Annotations:

	All annotations follow the same style:
		'//!' marks the beginning of a annotation line. (Using annotation blocks /*! ... */ would
		prevent block-wise commenting which is very usefull!)

		The annotation may contains a short description what the function is doing.

		Parameters can be described more detaild with a '@param' tag followed by the parameter name
		and the decribtion (e.g. //! @param win an ordinary window).

		Return values are further describted useing the '@return' tag.

		References to other functions (or classes) can be written via a '@see' tag. This is
		recommended for functions (or classes) depending on ther functions (or classes) or
		complement an other function (e.g. a setter references the getter).
