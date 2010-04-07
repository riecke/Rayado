// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A set of utilities for timing
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <time.h>
#include "Timing.hpp"

int64_t getMicroTime()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (t.tv_nsec / 1000) + t.tv_sec * 1000000;
}

int busyWait(int v)
{
    int j = 0;
    for (int i=0; i < v * TIMING_FACTOR; i++) {
	j += i;
    }
    return j;
}
