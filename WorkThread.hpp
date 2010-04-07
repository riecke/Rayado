// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a worker thread; takes tasks off the work queue when done.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__WorkThread_hpp__)
#define __WorkThread_hpp__

#include <Poco/Runnable.h>

class WorkQueue;

class WorkThread : public Poco::Runnable {
public:
    // Constructor/destructor
    WorkThread(WorkQueue * queue) { _queue = queue; } 
    virtual ~WorkThread() { }

    // Run the thread
    void run();

private:
    WorkQueue * _queue;

    WorkThread(const WorkThread & x);               // No copy constructor
    WorkThread & operator =(const WorkThread & x);  // No assignment
};

#endif
