// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of feeders, that send messages to the streams at a given rate.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <stdio.h>

#include "DataflowNode.hpp"
#include "Message.hpp"
#include "Source.hpp"
#include "Timing.hpp"

#include <sys/types.h>

// Main processing loop
void 
Source::onTimer(Poco::Timer & timer)
{
    for (int i=0; i < _messagesPerMs; i++) {
	Message * m = new Message(getMicroTime());
	_node->receive(m);
	_total--;
    }
    _node->commit();
    if (_total <= 0) {
	_timer.restart(0);
	_done.set();
    }
}

// Start the source
void
Source::start()
{
    Poco::TimerCallback<Source> callback(*this, &Source::onTimer);
    int interval = max(1, 1000/_rate);
    _timer.setPeriodicInterval(interval);
    _timer.start(callback);
}
