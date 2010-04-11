// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a thread queue (queue in front of the nodes).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__NodeQueueNoFlip_hpp__)
#define __NodeQueueNoFlip_hpp__

#include <deque>
#include <Poco/Mutex.h>

#include "NodeQueue.hpp"

using namespace std;

class Message;

class NodeQueueNoFlip : public NodeQueue {
public:
    // Constructor/destructor
    NodeQueueNoFlip() : NodeQueue() {}
    virtual ~NodeQueueNoFlip() {}

    // Get size
    uint64_t size();

    // Flip the read/write queues
    virtual void flip() {}

    // Push/pop
    virtual void push(Message *);
    Message * pop();

protected:
    deque<Message *> _queue;
    Poco::Mutex _queueLock;

private:
    NodeQueueNoFlip(const NodeQueueNoFlip & x);               // No copy constructor
    NodeQueueNoFlip & operator =(const NodeQueueNoFlip & x);  // No assignment
};

#endif
