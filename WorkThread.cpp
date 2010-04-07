// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a worker thread; takes tasks off the work queue when done.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <assert.h>

#include "PoolNode.hpp"
#include "WorkQueue.hpp"
#include "WorkThread.hpp"

// Run the thread
void 
WorkThread::run()
{
    while (true) {
	PoolNode * p = _queue->pop();
	assert(p != NULL);
	p->start();
    }
}
