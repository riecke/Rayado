// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A set of utilities for timing
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__Timing_hpp__)
#define __Timing_hpp__

#include <stdint.h>

static const int TIMING_FACTOR=100;
int64_t getMicroTime();
int busyWait(int v);

#endif
