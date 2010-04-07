// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a priority-based work queue (using locking).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__PriorityWorkQueue_hpp__)
#define __PriorityWorkQueue_hpp__

#include <ext/pb_ds/priority_queue.hpp>
#include <map>

#include <Poco/Condition.h>
#include <Poco/Mutex.h>

#include "WorkQueue.hpp"

using namespace std;

class Message;

class PriorityWorkQueue : public WorkQueue {
public:
    // Constructor/destructor
    PriorityWorkQueue() { } 
    virtual ~PriorityWorkQueue() { }

    // Push work into the queue
    void push(PoolNode *);

    // Pop work from the queue (will block the thread if nothing there)
    PoolNode * pop();

private:
    struct Compare {
	bool operator()(PoolNode * a, PoolNode * b) {
	    return a->getQueueSize() < b->getQueueSize();
	}
    };
    typedef __gnu_pbds::priority_queue<PoolNode *, Compare> nodeQueue_t;
    nodeQueue_t _queue;
    map<PoolNode *, nodeQueue_t::point_iterator> _inQueue;
    Poco::Condition _queueNonEmpty;
    Poco::Mutex _queueLock;

    PriorityWorkQueue(const PriorityWorkQueue & x);               // No copy constructor
    PriorityWorkQueue & operator =(const PriorityWorkQueue & x);  // No assignment
};

#endif
