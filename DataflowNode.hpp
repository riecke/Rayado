// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A base class of nodes in the dataflow graph, mostly abstract.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__DataflowNode_hpp__)
#define __DataflowNode_hpp__

#include <set>
#include <string>
#include <vector>

#include <Poco/Condition.h>
#include <Poco/Mutex.h>

using namespace std;

class NodeQueue;
class Message;
class Target;

class DataflowNode {
public:
    // Constructor/destructor
    DataflowNode(string name, int delay, int size, bool blockingQueue, bool tbb);
    virtual ~DataflowNode();

    // Get name or delay
    inline string getName() { return _name;}
    inline int getDelay() { return _delay; }

    // Connect this node to a downstream node
    void addEdge(DataflowNode * target);

    // Set a target for logging latencies
    inline void setTarget(Target * s) { _target = s; }

    // Receive a message from another node
    virtual void receive(Message * m);

    // Commit a set of messages from another node
    virtual void commit() { }

    // Pop and process a message from the queue
    void process();

    // Start the node
    virtual void start() = 0;

protected:
    string _name;
    int _delay;   // Delay between processing an element, in microseconds
    int _downstream;
    Target * _target;
    set<DataflowNode *> _downstreamSet;
    vector<DataflowNode *> _downstreamNodes;
    NodeQueue * _queue;

private:
    DataflowNode(const DataflowNode & x);               // No copy constructor
    DataflowNode & operator =(const DataflowNode & x);  // No assignment
};

#endif
