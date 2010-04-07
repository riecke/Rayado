// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of targets that write latency data to a file
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__Target_hpp__)
#define __Target_hpp__

#include <stdint.h>
#include <stdio.h>

#include <stdexcept>
#include <string>

using namespace std;

class Target {
public:
    // Constructor/destructor
    Target(const string & file);
    virtual ~Target();
    
    // Write latency
    void write(uint64_t val);
    
private:
    FILE * _file;
    
    Target(const Target & x);               // No copy constructor
    Target & operator =(const Target & x);  // No assignment
};

#endif
