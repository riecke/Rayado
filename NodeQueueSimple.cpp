// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A simple class for a thread queue (queue in front of the nodes).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <assert.h>
#include "Debug.hpp"
#include "NodeQueueSimple.hpp"

uint64_t
NodeQueueSimple::size()
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    return _queue.size();
}    

// Put a message into the queue---called from another thread
void 
NodeQueueSimple::push(Message * m)
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    debugOut("Push: %s, queue %lu\n", _name.c_str(), _queue.size());
    _queue.push_back(m);
}    

void
NodeQueueSimple::flip()
{
    // wait until the queue is nonempty
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    assert(_readQueue.empty());
    //fprintf(stderr, "Flip: queue %p %lu %d\n", this, _queue.size(), _queue.empty());    
    _queue.swap(_readQueue);
}

Message *
NodeQueueSimple ::pop()
{
    // get the message
    if (_readQueue.empty()) {
	return NULL;
    }
    debugOut("Pop: queue %lu\n", _readQueue.size());
    //fprintf(stderr, "Pop: queue %p %lu %d\n", this, _readQueue.size(), _readQueue.empty());
    Message * m = _readQueue.front();
    _readQueue.pop_front();
    return m;
}
