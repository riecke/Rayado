// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A base class of nodes in the dataflow graph, mostly abstract.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

//#define DEBUG

#include <assert.h>

#include <Poco/Condition.h>
#include <Poco/Mutex.h>

#include "DataflowNode.hpp"
#include "Debug.hpp"
#include "Message.hpp"
#include "NodeQueueBlocking.hpp"
#include "NodeQueueSimple.hpp"
#include "Target.hpp"
#include "Timing.hpp"

DataflowNode::DataflowNode(string name, int delay, int size, bool blockingQueue, bool tbb):
    _name(name), _delay(delay), _downstream(0), _target(NULL)
{
    if (blockingQueue) {
	_queue = new NodeQueueBlocking(size);
    } else {
	_queue = new NodeQueueSimple();
    }
}

DataflowNode::~DataflowNode() 
{
    delete _queue;
}

void 
DataflowNode::addEdge(DataflowNode * target) 
{ 
    if (_downstreamSet.find(target) == _downstreamSet.end()) {
	_downstreamSet.insert(target); 
	_downstreamNodes.push_back(target);
	_downstream++;
    }
}

void
DataflowNode::receive(Message * m)
{
    _queue->push(m); 
}

// Process a message
void
DataflowNode::process()
{
    // get and process the messages
    _queue->flip();    
    Message * m;
    while ((m = _queue->pop()) != NULL) {
	debugOut("Process0 %s %ld\n", _name.c_str(), getMicroTime());
	busyWait(_delay);
	debugOut("Process1 %s %ld\n", _name.c_str(), getMicroTime());
	
	// send downstream
	for (int i=0; i < _downstream; i++) {
	    _downstreamNodes[i]->receive(new Message(*m));
	}
	if (_target) {
	    //printf("intime %ld %ld %ld\n", getMicroTime(), m->_intime, getMicroTime() - m->_intime);
	    _target->write(getMicroTime() - m->_intime);
	}
	delete m;
    }
    for (int i=0; i < _downstream; i++) {
	_downstreamNodes[i]->commit();
    }
}
