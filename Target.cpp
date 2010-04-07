// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A class of targets that write latency data to a file
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include "Target.hpp"

// Constructor/destructor
Target::Target(const string & file)
{
    _file = fopen(file.c_str(), "w+");
    if (!_file) {
	throw runtime_error("File open failed: " + file);
    }
}
 
Target::~Target()
{
    fclose(_file);
}
    
// Write latency
void 
Target::write(uint64_t val)
{
    fwrite(&val, sizeof(uint64_t), 1, _file);
}
    
