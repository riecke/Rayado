// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class for a dataflow graph.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__DataflowGraph_hpp__)
#define __DataflowGraph_hpp__

#include <stdio.h>

#include <map>
#include <set>
#include <string>

using namespace std;

class DataflowNode;
class Source;

class DataflowGraph {

public:
    // Constructor/destructor
    DataflowGraph(): _poolMode(false), _tbbMode(true), _queueSize(1024), _poolSize(2) {}
    virtual ~DataflowGraph() {}

    // Get/set properties
    inline bool getPoolMode()       { return _poolMode; }
    inline bool getTbbMode()        { return _tbbMode; }
    inline int getPoolSize()        { return _poolSize; }
    inline bool getQueueSize()      { return _queueSize; }

    inline void setPoolMode(bool b) { _poolMode = b; }
    inline void setTbbMode(bool b)  { _tbbMode = b; }
    inline void setPoolSize(int s)  { _poolSize = s; }
    inline void setQueueSize(int q) { _queueSize = q; }

    // Add a node to the graph
    void addNode(const string & node, int delay);

    // Add an edge to the graph (which means that the target won't be an input)
    void addEdge(const string & src, const string & dst);

    // Add a source to the graph
    void addSource(const string & name, int rate, int total);

    // Add a target to the graph (this writes out 64-bit latencies in binary form to a file)
    void addTarget(const string & name, const string & filename);

    // Start the simulation
    void start(); 

private:
    bool _poolMode;
    bool _tbbMode;
    int _poolSize;
    int _queueSize;
    map<string, DataflowNode *> _nodes;
    set<DataflowNode *> _inputs;
    set<Source *> _sources;

    void addNode(DataflowNode * node);
    void addEdge(DataflowNode * src, DataflowNode * dst);
    DataflowNode * getNode(const string & name);

    DataflowGraph(const DataflowNode & x);                // No copy constructor
    DataflowGraph & operator =(const DataflowGraph & x);  // No assignment
};

#endif
