// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a dataflow graph.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <stdexcept>

#include <Poco/Thread.h>

#include "DataflowGraph.hpp"
#include "PoolNode.hpp"
#include "PriorityWorkQueue.hpp"
#include "Source.hpp"
#include "Target.hpp"
#include "ThreadNode.hpp"
#include "WorkQueue.hpp"
#include "WorkThread.hpp"

using namespace std;

// Add a node to the graph
void 
DataflowGraph::addNode(const string & name, int delay)
{
    DataflowNode * node = _poolMode ? 
	(DataflowNode *) new PoolNode(name, delay, _queueSize, _flipMode) : 
	(DataflowNode *) new ThreadNode(name, delay, _queueSize, _tbbMode, _flipMode);
    _nodes[name] = node;
}

// Add an edge to the graph
void 
DataflowGraph::addEdge(const string & src, const string & dst)
{
    DataflowNode * srcn = getNode(src);
    DataflowNode * dstn = getNode(dst);
    if (srcn == NULL || dstn == NULL) {
	throw runtime_error("Attempt to add bad edge: " + src + "->" + dst);
    }
    srcn->addEdge(dstn);
}

// Lookup a node in the graph; return NULL if not there
DataflowNode * 
DataflowGraph::getNode(const string & name)
{
    map<string, DataflowNode *>::iterator i = _nodes.find(name);
    return (i == _nodes.end()) ? NULL : i->second;
}

// Add a source to the graph
void 
DataflowGraph::addSource(const string & src, int rate, int total)
{
    DataflowNode * srcn = getNode(src);
    if (srcn == NULL) {
	throw runtime_error("Attempt to add bad source: " + src);
    }
    Source * s = new Source(srcn, rate, total);
    _sources.insert(s);
}

// Add a target to the graph
void 
DataflowGraph::addTarget(const string & src, const string & file)
{
    DataflowNode * srcn = getNode(src);
    if (srcn == NULL) {
	throw runtime_error("Attempt to add bad target: " + src);
    }
    Target * s = new Target(file);
    srcn->setTarget(s);
}

// Start the run
void 
DataflowGraph::start()
{
    // start the nodes first
    if (_poolMode) {
	WorkQueue * workQueue = new PriorityWorkQueue();
	for (map<string, DataflowNode *>::iterator i = _nodes.begin(); i != _nodes.end(); ++i) {
	    PoolNode * p = dynamic_cast<PoolNode *> (i->second);
	    p->setWorkQueue(workQueue);
	}
	for (int i=0; i < _poolSize; i++) {
	    Poco::Thread * t = new Poco::Thread();
	    WorkThread * work = new WorkThread(workQueue);
	    t->start(*work);
	}
    } else {
	for (map<string, DataflowNode *>::iterator i = _nodes.begin(); i != _nodes.end(); ++i) {
	    i->second->start();
	}
    }

    // start the sources
    for (set<Source *>::iterator i = _sources.begin(); i != _sources.end(); ++i) {
	(*i)->start();
    }

    // join the sources
    for (set<Source *>::iterator i = _sources.begin(); i != _sources.end(); ++i) {
	(*i)->join();
    }
    
}

