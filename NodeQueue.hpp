// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A abstract class for a thread queue (queue in front of the nodes).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__NodeQueue_hpp__)
#define __NodeQueue_hpp__

#include <stdint.h>

class Message;

class NodeQueue {
public:
    // Constructor/destructor
    NodeQueue() {}
    virtual ~NodeQueue() {}

    // Get size
    virtual uint64_t size() = 0;

    // Flip the read/write queues
    virtual void flip() = 0;

    // Push/pop
    virtual void push(Message *) = 0;
    virtual Message * pop() = 0;

private:
    NodeQueue(const NodeQueue & x);               // No copy constructor
    NodeQueue & operator =(const NodeQueue & x);  // No assignment
};

#endif
