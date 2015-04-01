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

int main(int argc, const char * argv[]) 
{
	// Assignment 1
	std::cout << "*** Assignment 1 - Scheduling problem ***" << std::endl;
	assignment1::scheduling_problem("data/jobs.txt");
	std::cout << "*** Assignment 1 - Prim's algorithm ***" << std::endl;
	assignment1::prims_algorithm("data/edges.txt");
}
