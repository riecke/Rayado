// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// This file defines a class of messages, which are just used for latency measurements.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__Message_hpp__)
#define __Message_hpp__

#include <stdint.h>

class Message {
public:
    uint64_t _intime;
    uint64_t _outtime;
    Message(uint64_t v) { _intime = v; }
    Message(const Message & x) { _intime = x._intime; _outtime = x._outtime; }
};

#endif
