// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// This file contains a collection of functions for parsing a dataflow test file.
// The file must have the form
//
//   # Comments (lines starting with #) and empty lines are ignored
//   [general]
//   pool <n> | nopool 
//   queue <queue size>
//
//   [nodes]
//   <name0> <delay0>  (delay in milliseconds)
//   ...
//
//   [edges]
//   <namei> <namej>
//   ...
//
//   [sources]
//   <name0> <rate0>   (rate in messages/second)
//   ...
//
//   [targets]
//   <name0> <binary output file0>
//   ...
// 
// It then constructs the graph (using the base class of nodes).
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <stdlib.h>

#include <fstream>

#define DEBUG

#include "Debug.hpp"
#include "ReadConfiguration.hpp"

using namespace std;

void splitString(string & input, string & field1, string & field2)
{
    size_t pos = input.find_first_of(' ');
    if (pos != string::npos) {
	field1 = input.substr(0, pos);
	field2 = input.substr(pos+1);
    } else {
	field1 = input;
    }
}

DataflowGraph * readFileAsString(const string & filename)
{
    string line, field1, field2;
    DataflowGraph * graph = new DataflowGraph();
    ifstream input(filename.c_str());
    bool poolMode = false;
    bool generalMode = false;
    bool nodeMode = false;
    bool edgeMode = false;
    bool sourceMode = false;
    bool targetMode = false;
    while (getline(input,line)) {
	if (line.length() < 1 || line[0] == '#') {
	    // skip comments and empty lines
	    continue;
	}

	splitString(line, field1, field2);
	if (line == "[general]") {
	    generalMode = true;
	} else if (line == "[nodes]") {
	    generalMode = false;
	    nodeMode = true;
	} else if (line == "[edges]") {
	    nodeMode = false;
	    edgeMode = true;
	} else if (line == "[sources]") {
	    edgeMode = false;
	    sourceMode = true;
	} else if (line == "[targets]") {
	    sourceMode = false;
	    targetMode = true;
	} else if (generalMode) {
	    if (field1 == "pool") {
  	        poolMode = true;
		graph->setPoolMode(true);
		graph->setPoolSize(atoi(field2.c_str()));
	    } else if (field1 == "nopool") {
  	        poolMode = false;
		graph->setPoolMode(false);
		graph->setTbbMode(false);
	    } else if (field1 == "queue") {
		int size = atoi(field2.c_str());
		graph->setQueueSize(size);
	    }
	} else if (nodeMode) {
	    int delay = atoi(field2.c_str());
	    debugOut("Adding node '%s', delay %d\n", field1.c_str(), delay);
	    graph->addNode(field1, delay);
	} else if (edgeMode) {
	    debugOut("Adding edge '%s' -> '%s'\n", field1.c_str(), field2.c_str());
	    graph->addEdge(field1, field2);
	} else if (sourceMode) {
	    string rateS, totalS;
	    splitString(field2, rateS, totalS);
	    int rate = atoi(rateS.c_str());	
	    int total = atoi(totalS.c_str());
	    if (total == 0) {
		total = 2000000000;
	    }
	    debugOut("Adding source '%s', rate %d, total %d\n", field1.c_str(), rate, total);
	    graph->addSource(field1, rate, total);
	} else if (targetMode) {
	    debugOut("Adding target '%s', file %s\n", field1.c_str(), field2.c_str());
	    graph->addTarget(field1, field2);
	}
    }
    return graph;
}


