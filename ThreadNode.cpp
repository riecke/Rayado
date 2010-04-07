// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of nodes using threads.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <Poco/Thread.h>

#include "Debug.hpp"
#include "ThreadNode.hpp"

// Run the node
void
ThreadNode::run()
{
    while (true) {
	process();
    }
}

// Start the node, which creates a thread for it
void
ThreadNode::start()
{
    Poco::Thread * t = new Poco::Thread();
    t->start(*this);
}

