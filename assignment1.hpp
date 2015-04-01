//
//  assignment1.cpp
//  Algorithms: Design and Analysis, Part 2
//
//  Programming Assignment 1
//
//  Created by Nenad Mancevic on 4/1/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem 1: Scheduling problem
//
/***********************
1.1 
In this programming problem and the next you'll code up the greedy algorithms 
from lecture for minimizing the weighted sum of completion times.. 
Download the text file here (http://bit.ly/1ajLrBi). 
This file describes a set of jobs with positive and integral weights and lengths. 
It has the format
[number_of_jobs]
[job_1_weight] [job_1_length]
[job_2_weight] [job_2_length]
...
For example, the third line of the file is "74 59", indicating that the second job 
has weight 74 and length 59. You should NOT assume that edge weights or lengths 
are distinct.

Your task in this problem is to run the greedy algorithm that schedules jobs in 
decreasing order of the difference (weight - length). Recall from lecture that 
this algorithm is not always optimal. IMPORTANT: if two jobs have equal difference 
(weight - length), you should schedule the job with higher weight first. 
Beware: if you break ties in a different way, you are likely to get the wrong answer. 

You should report the sum of weighted completion times of the resulting schedule.

1.2
For this problem, use the same data set as in the previous problem. 
Your task now is to run the greedy algorithm that schedules jobs (optimally) 
in decreasing order of the ratio (weight/length). In this algorithm, it does not 
matter how you break ties. You should report the sum of weighted completion times 
of the resulting schedule.
************************/

#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

namespace assignment1
{
	
	void scheduling_problem(const std::string& inputFile)
	{
		/// SOLUTION TO THIS AND THE NEXT PROBLEM WILL BE POSTED AFTER THE DEADLINE!
	}

	void prims_algorithm(const std::string& inputFile)
	{
		/// AFTER DEADLINE!
	}

} // namespace
