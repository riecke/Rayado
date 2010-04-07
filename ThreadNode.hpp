// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of nodes using threads.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__ThreadNode_hpp__)
#define __ThreadNode_hpp__

#include <Poco/Runnable.h>

#include "DataflowNode.hpp"
#include "Message.hpp"

class ThreadNode : public DataflowNode, public Poco::Runnable {
public:
    // Constructor/destructor
    ThreadNode(string name, int delay, int size, bool tbb) : DataflowNode(name, delay, size, true, tbb) { } 
    virtual ~ThreadNode() { }

    // Start the node
    void start();

private:
    // Override for Runnable interface
    void run();

    ThreadNode(const ThreadNode & x);               // No copy constructor
    ThreadNode & operator =(const ThreadNode & x);  // No assignment
};

#endif
