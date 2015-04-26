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
#include "assignment3.hpp"
#include "assignment4.hpp"

int main(int argc, const char * argv[]) 
{
    ///////////////////// Assignment 1 //////////////////////////
	std::cout << "*** Assignment 1 - Scheduling problem ***" << std::endl;
	assignment1::scheduling_problem::run_algorithm("data/jobs.txt");

	std::cout << std::endl << "*** Assignment 1 - Prim's algorithm - Test Case 1 ***" << std::endl;
	if (assignment1::prims_algorithm::test1())
		std::cout << "... Test passed!" << std::endl;

	std::cout << "*** Assignment 1 - Prim's algorithm - Main Test Case ***" << std::endl;
	assignment1::prims_algorithm::run_algorithm("data/edges.txt");

    ///////////////////// Assignment 2 //////////////////////////
    std::cout << std::endl << "*** Assignment 2 - UnionFind Test Case 1 ***" << std::endl;
    if (DataStructures::TestCase1())
        std::cout << "... Test passed!" << std::endl;

    std::cout << "*** Assignment 2 - Clustering - Max-Spacing K=4 Clustering ***" << std::endl;
    int max_spacing = assignment2::four_clustering::four_clustering("data/clustering1.txt");
    std::cout << "Max-Spacing clustering is: " << max_spacing << std::endl;

    std::cout << "*** Assignment 2 - Big Clustering - Hamming distance ***" << std::endl;
    assignment2::clustering_big::run_algorithm("data/clustering_big.txt");
    std::cout << "*** Assignment 2 - Big Clustering - Hamming distance - Faster Algorithm ***" << std::endl;
    assignment2::clustering_big::run_faster_algorithm("data/clustering_big.txt");

    ///////////////////// Assignment 3 //////////////////////////
    std::cout << std::endl << "*** Assignment 3 - Knapsack - Test Case 1 ***" << std::endl;
    if (assignment3::knapsack_1::testCase1())
        std::cout << "... Test passed!" << std::endl;
    std::cout << "*** Assignment 3 - Knapsack - Problem 1 ***" << std::endl;
    assignment3::knapsack_1::run_algorithm("data/knapsack1.txt");

    std::cout << "*** Assignment 3 - Knapsack - Problem 2 - Test Case 1 ***" << std::endl;
    if (assignment3::knapsack_big::testCase1())
        std::cout << "... Test passed!" << std::endl;
    std::cout << "*** Assignment 3 - Knapsack - Problem 2 ***" << std::endl;
    assignment3::knapsack_big::run_algorithm("data/knapsack_big.txt");

    ///////////////////// Assignment 4 //////////////////////////
    std::cout << std::endl << "*** Assignment 4 - All-Pairs Shortest Path ***" << std::endl;
    assignment4::run_algorithm("data/g1.txt");
    assignment4::run_algorithm("data/g2.txt");
    assignment4::run_algorithm("data/g3.txt");
}
