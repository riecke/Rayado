// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// An abstract class for a work queue.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__WorkQueue_hpp__)
#define __WorkQueue_hpp__

using namespace std;

class PoolNode;

class WorkQueue {
public:
    // Constructor/destructor
    WorkQueue() { } 
    virtual ~WorkQueue() { }

    // Push work into the queue
    virtual void push(PoolNode *) = 0;

    // Pop work from the queue (will block the thread if nothing there)
    virtual PoolNode * pop() = 0;
};

#endif
