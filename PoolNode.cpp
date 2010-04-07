// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of nodes using thread pools.
//
// The basic idea: have a statically allocated, work queue that holds nodes that are 
// ready to run.  The work queue is a priority queue: the 
// 1. When the node's queue becomes non-empty, put the node on the work queue.
// 2. When a thread in the pool becomes free, wait for something on the work queue
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#define DEBUG

#include "Debug.hpp"
#include "PoolNode.hpp"
#include "WorkQueue.hpp"

void
PoolNode::commit()
{
    _workQueue->push(this);
}

void
PoolNode::start()
{
    process();
    _idle = true;
    _workQueue->push(this);
}
