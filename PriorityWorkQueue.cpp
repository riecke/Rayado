// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a priority-based work queue (using locking).
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
#include "PriorityWorkQueue.hpp"


// Push node into the queue
void 
PriorityWorkQueue::push(PoolNode * n)
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    uint64_t size = n->getQueueSize();
    if (size == 0 || !n->getIdle()) {
	return;
    }
    debugOut("%ld: Push PriorityWorkQueue %p %lu\n", syscall(186), n, size);
    map<PoolNode *, nodeQueue_t::point_iterator>::iterator i = _inQueue.find(n);
    if (i == _inQueue.end()) {
	_inQueue[n] = _queue.push(n);
	_queueNonEmpty.signal();
    } else {
	_queue.modify(i->second, n);
    }
    debugOut("%ld: Push new size %lu\n", syscall(186), n->getQueueSize());
 }

// Pop node from the queue
PoolNode *
PriorityWorkQueue::pop()
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    debugOut("%ld: Pop PriorityWorkQueue %lu\n", syscall(186), _queue.size());
    while (_queue.size() == 0) {
	_queueNonEmpty.wait(_queueLock);
    }
    debugOut("%ld: Pop PriorityWorkQueue before assert %lu\n", syscall(186), _queue.size());
    PoolNode * n = _queue.top();
    n->setIdle(false);
    debugOut("%ld: Popped from PriorityWorkQueue %p %lu\n", syscall(186), n, n->getQueueSize());
    assert(n->getQueueSize() > 0);
    _queue.pop();
    _inQueue.erase(n);
    return n;
}    

