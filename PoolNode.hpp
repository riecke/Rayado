// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of nodes using thread pools.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__PoolNode_hpp__)
#define __PoolNode_hpp__

#include <stdint.h>
#include "DataflowNode.hpp"
#include "NodeQueue.hpp"

class WorkQueue;

class PoolNode : public DataflowNode {
public:
    // Constructor/destructor
    PoolNode(string name, int delay, int size) : 
	DataflowNode(name, delay, size, false, false), _idle(true) { } 
    virtual ~PoolNode() { }

    // Set the work queue
    void setWorkQueue(WorkQueue * w) { _workQueue = w; }

    // Get the size of the queue
    inline uint64_t getQueueSize() { return _queue->size(); }

    // Commit a set of messages from another node
    virtual void commit();

    // Start the node (this does nothing)
    void start();

    // Change state (idle or processing)
    inline bool getIdle() { return _idle; }
    inline void setIdle(bool b) { _idle = b; }

private:
    bool _idle;
    WorkQueue * _workQueue;

    PoolNode(const PoolNode & x);               // No copy constructor
    PoolNode & operator =(const PoolNode & x);  // No assignment
};

#endif
