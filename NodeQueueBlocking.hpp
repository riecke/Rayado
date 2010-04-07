// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a thread queue (queue in front of the nodes) that implements backpressure.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__NodeQueueBlocking_hpp__)
#define __NodeQueueBlocking_hpp__

#include <Poco/Condition.h>

#include "NodeQueueSimple.hpp"

using namespace std;

class Message;

class NodeQueueBlocking : public NodeQueueSimple {
public:
    // Constructor/destructor
    NodeQueueBlocking(int maxSize=1024): NodeQueueSimple(), _maxSize(maxSize) {}
    virtual ~NodeQueueBlocking() {}

    // Flip the read/write queues
    void flip();

    // Push/pop
    void push(Message *);

private:
    int _maxSize;
    Poco::Condition _queueNonEmpty;
    Poco::Condition _queueNonFull;

    NodeQueueBlocking(const NodeQueueBlocking & x);               // No copy constructor
    NodeQueueBlocking & operator =(const NodeQueueBlocking & x);  // No assignment
};

#endif
