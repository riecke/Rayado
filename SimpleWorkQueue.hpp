// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a simple work queue.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__SimpleWorkQueue_hpp__)
#define __SimpleWorkQueue_hpp__

#include <vector>

#include <Poco/Condition.h>
#include <Poco/Mutex.h>

#include "WorkQueue.hpp"

using namespace std;

class Message;

class SimpleWorkQueue : public WorkQueue {
public:
    // Constructor/destructor
    SimpleWorkQueue() { } 
    virtual ~SimpleWorkQueue() { }

    // Push work into the queue
    void push(PoolNode *);

    // Pop work from the queue (will block the thread if nothing there)
    PoolNode * pop();

private:
    vector<PoolNode *> _nodes;
    Poco::Condition _queueNonEmpty;
    Poco::Mutex _queueLock;

    SimpleWorkQueue(const SimpleWorkQueue & x);               // No copy constructor
    SimpleWorkQueue & operator =(const SimpleWorkQueue & x);  // No assignment
};

#endif
