// -*- mode: c++; c-basic-offset: 4 -*-

// ------------------------------------------------------------------------------------
// A program for analyzing latencies produced by the simulation.
//
// Copyright Jon Riecke, 2010.  All rights reserved.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------------

#include <set>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

using namespace std;


int main(int argc, char * argv[])
{
    if (argc != 2 && argc != 4) {
	printf("Usage: processLatency [-s <histogram size>] <datafile>\n");
	return 1;
    }
    bool stats;
    int buckets;
    char * filename;
    if (strcmp(argv[1], "-s") == 0) {
	stats = true;
	buckets=atoi(argv[2]);
	filename = argv[3];	
    } else {
	stats = false;
	filename = argv[1];
    }
    FILE * f = fopen(filename, "r+");
    if (f == NULL) {
        return 1;
    }
    uint64_t v, min=2000000000, max=0, count=0;
    double sum=0.0;
    multiset<uint64_t> vals;
    while (fread(&v, sizeof(uint64_t), 1, f) != 0) {
	if (!stats) printf("%lu\n", v);
	if (v < min) {
	    min = v;
	}
	if (v > max) {
	    max = v;
	}
	count++;
	sum += v;
	vals.insert(v);
    }
    if (stats) {
	printf("Total samples=%lu, max=%lu, min=%lu, mean=%f\n", count, max, min, sum/count);
	// range = [min, max]; max-min/16
	int bucket=0;
	count=0;
	uint64_t range=(max-min)/buckets;
	max=min+range;
	min=0;
	for (multiset<uint64_t>::iterator i=vals.begin(); i != vals.end(); ++i) {
	    uint64_t val=*i;
	    count++;
	    while (val > max) {
		printf("[%6lu, %6lu): %lu\n", min, max, count);
		bucket++;
		count=0;
		min=max;
		max += range;
	    }
	}
	printf("[%6lu, %6lu): %lu\n", min, max, count);
    }
    return 0;
}
