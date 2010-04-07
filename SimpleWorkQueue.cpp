// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a simple work queue.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

//#define DEBUG

#include <assert.h>

#include "Debug.hpp"
#include "PoolNode.hpp"
#include "SimpleWorkQueue.hpp"


// Push node into the queue
void 
SimpleWorkQueue::push(PoolNode * n)
{
    _event.set();
 }

// Pop node from the queue
PoolNode *
SimpleWorkQueue::pop()
{
    _event.wait();
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    debugOut("%ld: Pop SimpleWorkQueue %lu\n", syscall(186), _queue.size());
    while (_queue.size() == 0) {
	_queueNonEmpty.wait(_queueLock);
    }
    debugOut("%ld: Pop SimpleWorkQueue before assert %lu\n", syscall(186), _queue.size());
    PoolNode * n = _queue.top();
    n->setIdle(false);
    debugOut("%ld: Popped from SimpleWorkQueue %p %lu\n", syscall(186), n, n->getQueueSize());
    assert(n->getQueueSize() > 0);
    _queue.pop();
    _inQueue.erase(n);
    return n;
}    

