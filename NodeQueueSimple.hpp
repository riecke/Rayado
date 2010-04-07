// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a thread queue (queue in front of the nodes).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__NodeQueueSimple_hpp__)
#define __NodeQueueSimple_hpp__

#include <deque>
#include <Poco/Mutex.h>

#include "NodeQueue.hpp"

using namespace std;

class Message;

class NodeQueueSimple : public NodeQueue {
public:
    // Constructor/destructor
    NodeQueueSimple() : NodeQueue() {}
    virtual ~NodeQueueSimple() {}

    // Get size
    uint64_t size();

    // Flip the read/write queues
    virtual void flip();

    // Push/pop
    virtual void push(Message *);
    Message * pop();

protected:
    deque<Message *> _queue;
    deque<Message *> _readQueue;
    Poco::Mutex _queueLock;

private:
    NodeQueueSimple(const NodeQueueSimple & x);               // No copy constructor
    NodeQueueSimple & operator =(const NodeQueueSimple & x);  // No assignment
};

#endif
