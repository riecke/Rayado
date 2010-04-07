// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// This file contains a collection of functions for parsing a dataflow test file.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#if !defined(__ReadConfiguration_hpp__)
#define __ReadConfiguration_hpp__

#include <string>
#include "DataflowGraph.hpp"

using namespace std;

DataflowGraph * readFileAsString(const string & filename);

#endif


