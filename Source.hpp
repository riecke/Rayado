// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of feeders, that send messages to the streams at a given rate.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__Source_hpp__)
#define __Source_hpp__

#include <Poco/Event.h>
#include <Poco/Timer.h>

#include <string>

using namespace std;

class DataflowNode;

class Source {
public:
    // Constructor/destructor
    Source(DataflowNode * node, int rate, int total): 
	_node(node), _rate(rate), _total(total) 
    {
	_messagesPerMs = max(1,_rate/1000);
    }
    
    virtual ~Source() { }

    // Get name or delay
    inline string getName() { return _node->getName();}
    inline int getRate() { return _rate; }

    // Start the source, which starts the timer
    void start();

    // Join the source
    void join() { _done.wait(); }

private:
    int _rate;          // Rate for sending messages to the node (in messages/second)
    int _total;         // Total number of messages
    int _messagesPerMs; // Messages to send per millisecond
    DataflowNode * _node;
    Poco::Timer _timer;
    Poco::Event _done;

    void onTimer(Poco::Timer &);

    Source(const Source & x);               // No copy constructor
    Source & operator =(const Source & x);  // No assignment
};

#endif
