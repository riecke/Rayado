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
#include "NodeQueueNoFlip.hpp"

uint64_t
NodeQueueNoFlip::size()
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    return _queue.size();
}    

// Put a message into the queue---called from another thread
void 
NodeQueueNoFlip::push(Message * m)
{
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    debugOut("Push: %s, queue %lu\n", _name.c_str(), _queue.size());
    _queue.push_back(m);
}    

Message *
NodeQueueNoFlip::pop()
{
    // get the message
    Poco::ScopedLock<Poco::Mutex> l(_queueLock);
    if (_queue.empty()) {
	return NULL;
    }
    debugOut("Pop: queue %lu\n", _queue.size());
    //fprintf(stderr, "Pop: queue %p %lu %d\n", this, _queue.size(), _queue.empty());
    Message * m = _queue.front();
    _queue.pop_front();
    return m;
}
