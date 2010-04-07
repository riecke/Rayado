// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a thread queue (queue in front of the nodes) that implements backpressure.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <assert.h>
#include "Debug.hpp"
#include "NodeQueueBlocking.hpp"

// Put a message into the queue---called from another thread
void 
NodeQueueBlocking::push(Message * m)
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    debugOut("Push: %s, queue %lu\n", _name.c_str(), _queue.size());
    if (_queue.size() > _maxSize) {
	debugOut("Full wait %s\n", _name.c_str());
	_queueNonFull.wait(_queueLock);
    }
    _queue.push_back(m);
    _queueNonEmpty.signal();
}    

void
NodeQueueBlocking::flip()
{
    // wait until the queue is nonempty
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    if (_queue.empty()) {
	debugOut("Empty wait %s\n", _name.c_str());
	_queueNonEmpty.wait(_queueLock);
    }
    //fprintf(stderr, "Flip: queue %p %lu %d\n", this, _queue.size(), _queue.empty());    
    _queue.swap(_readQueue);
    _queueNonFull.signal();
}
