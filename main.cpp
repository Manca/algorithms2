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
#include "assignment2.hpp"
//#include "lib\UnionFind.hpp"

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

    std::cout << std::endl << "*** Assignment 2 - Clustering - Max-Spacing K=4 Clustering ***" << std::endl;
//	DataStructures::TestCase1();
//	DataStructures::TestCase2("data/uf_test_cases/tinyUF.txt");
    int max_spacing = assignment2::four_clustering::four_clustering("data/clustering1.txt");
    std::cout << "Max-Spacing clustering is: " << max_spacing << std::endl;
}
