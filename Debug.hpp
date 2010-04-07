// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// Auxiliary stuff for debugging.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__Debug_hpp__)
#define __Debug_hpp__

#include <stdio.h>

#if defined(DEBUG)
#define debugOut(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
#define debugOut(format, ...) 
#endif

#endif
