//
//  main.cpp
//  Algorithms: Design and Analysis, Part 2
//
//  Created by Nenad Mancevic on 4/1/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
// Main program - all our assignments will be executed from here

#include <iostream>

#include "assignment1.hpp"
#include "lib\UnionFind.hpp"

int main(int argc, const char * argv[]) 
{
	// Assignment 1
/*	std::cout << "*** Assignment 1 - Scheduling problem ***" << std::endl;
	assignment1::scheduling_problem::run_algorithm("data/jobs.txt");

	std::cout << std::endl << "*** Assignment 1 - Prim's algorithm - Test Case 1 ***" << std::endl;
	if (assignment1::prims_algorithm::test1())
		std::cout << "... Test passed!" << std::endl;

	std::cout << "*** Assignment 1 - Prim's algorithm - Main Test Case ***" << std::endl;
	assignment1::prims_algorithm::run_algorithm("data/edges.txt");*/

	DataStructures::TestCase1();
	DataStructures::TestCase2("data/uf_test_cases/tinyUF.txt");
}
