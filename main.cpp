// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// main control for "dataflow"
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <stdexcept>
#include "ReadConfiguration.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc != 2) {
	printf("Usage: dataflow <config>\n");
	return 1;
    }
    string file = argv[1];
    DataflowGraph * graph = NULL;
    try {
	graph = readFileAsString(file);
    } catch (runtime_error e) {
	printf("Usage: dataflow <config>\n");
	printf("  Error found in configuration file: %s\n", e.what());
	return 1;
    }
    if (graph == NULL) {
	printf("Usage: dataflow <config>\n");
	printf("  Unknown error found in configuration file.\n");
	return 1;
    }
    graph->start();
    return 0;  
}
