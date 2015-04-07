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
//
//  Problem 2: Prim's Minimum Spanning Tree Algorithm
//
/***********************
In this programming problem you'll code up Prim's minimum spanning tree algorithm. 
Download the text file here (http://bit.ly/1BRDgTh). 
This file describes an undirected graph with integer edge costs. It has the format
[number_of_nodes] [number_of_edges]
[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]
[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
...
For example, the third line of the file is "2 3 -8874", indicating that there is an edge 
connecting vertex #2 and vertex #3 that has cost -8874. You should NOT assume that edge 
costs are positive, nor should you assume that they are distinct.

Your task is to run Prim's minimum spanning tree algorithm on this graph. 
You should report the overall cost of a minimum spanning tree.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation 
of Prim's algorithm should work fine. OPTIONAL: For those of you seeking an additional challenge, 
try implementing a heap-based version. The simpler approach, which should already give you a healthy 
speed-up, is to maintain relevant edges in a heap (with keys = edge costs). 
The superior approach stores the unprocessed vertices in the heap, as described in lecture. 
Note this requires a heap that supports deletions, and you'll probably need to maintain some kind 
of mapping between vertices and their positions in the heap.
************************/

#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <assert.h>
#include <iostream>

namespace assignment1
{
	namespace scheduling_problem
	{
		typedef std::tuple<int, int> job;	// job is a tuple of (weight, length)

		/* Compute score for each job in a vector as a function of job weight - job length */
		std::vector<std::tuple<int, job>> computeScoreDiff(const std::vector<job>& jobs)
		{
			std::vector<std::tuple<int, job>> scores;	// we'll assign score for each job

			for (auto job : jobs)
			{
				int score = std::get<0>(job) - std::get<1>(job);
				scores.push_back(std::make_tuple(score, job));
			}

			return scores;
		}

		/* Compute score for each job in a vector as a function of job weight / job length */
		std::vector<std::tuple<double, job>> computeScoreRatio(const std::vector<job>& jobs)
		{
			std::vector<std::tuple<double, job>> scores;	// we'll assign score for each job

			for (auto job : jobs)
			{
				double score = (double)std::get<0>(job) / std::get<1>(job);	// wj / lj
				scores.push_back(std::make_tuple(score, job));
			}

			return scores;
		}

		long long schedule_by_difference(const std::vector<job>& jobs)
		{
			auto scores = computeScoreDiff(jobs);
			// schedule jobs by decreasing value of scores
			std::sort(scores.begin(), scores.end(), [](std::tuple<int, job> a, std::tuple<int, job> b)
			{
				return a > b;
			});

			long long weighted_sum = 0;
			int total_length = 0;

			for (auto sorted_jobs : scores)	// we get the job
			{
				auto job = std::get<1>(sorted_jobs);
				total_length += std::get<1>(job);
				weighted_sum += std::get<0>(job) * total_length;	// wj*cj
			}

			return weighted_sum;
		}

		long long schedule_by_ratio(const std::vector<job>& jobs)
		{
			auto scores = computeScoreRatio(jobs);
			// schedule jobs by decreasing value of scores
			std::sort(scores.begin(), scores.end(), [](std::tuple<double, job> a, std::tuple<double, job> b)
			{
				return a > b;
			});

			long long weighted_sum = 0;
			int total_length = 0;

			for (auto sorted_jobs : scores)	// we get the job
			{
				auto job = std::get<1>(sorted_jobs);
				total_length += std::get<1>(job);
				weighted_sum += std::get<0>(job) * total_length;	// wj*cj
			}

			return weighted_sum;
		}

		void run_algorithm(const std::string& inputFile)
		{
			std::vector<job> jobs;
			std::ifstream file(inputFile, std::ios::in);

			if (file.is_open())
			{
				int n;
				int job_weight, job_length;

				file >> n;
				while (file >> job_weight >> job_length)
				{
					std::tuple<int, int> job = std::make_tuple(job_weight, job_length);

					jobs.push_back(job);
				}
				file.close();

				// Schedule by difference total weighted sum
				long long schedule_by_diff_sum = schedule_by_difference(jobs);
				std::cout << "Schedule by difference total weighted sum: " << schedule_by_diff_sum << std::endl;

				assert(schedule_by_diff_sum == 69119377652);

				// Schedule by ratio total weighted sum
				long long schedule_by_ratio_sum = schedule_by_ratio(jobs);
				std::cout << "Schedule by ratio total weighted sum: " << schedule_by_ratio_sum << std::endl;

				assert(schedule_by_ratio_sum == 67311454237);
			}
		}
	} // namespace

	namespace prims_algorithm
	{
		typedef std::tuple<int, int, int> Edge;	// edge has: source vertex, destination vertex and edge cost
		typedef std::map<int, std::vector<Edge>> Graph;		// source vertex connected to destination vertex vector (name, edge_cost)

		long long prims_algorithm(Graph& g)
		{
			long long result = 0;
			std::vector<int> X = { 1 };		// vertices spanned by tree T so far (initialize X with first vertex in first edge)
			std::vector<Edge> T;			// T is initially empty (tree_so_far)

			while (X.size() != g.size())
			{
				// let's go over all vertices in X so far and find adjancent min cost nodes
				Edge min_cost_edge;
				int min = 9999999;
				for (int u : X)	// always need to find the cheapest edge from whole set of adjacent vertices to set X
				{
					// search min cost edge
					for (auto edge : g[u])
					{
						if (std::find(X.begin(), X.end(), std::get<1>(edge)) == X.end()) // if target vertex is not in X
						{
							if (std::get<2>(edge) < min)
							{
								min_cost_edge = edge;
								min = std::get<2>(edge);
							}
						}
					}
				}
				// finally add the cheapest node overall (going out from X) and add destination node to X
				T.push_back(min_cost_edge);
				X.push_back(std::get<1>(min_cost_edge));	// add destination vertex to X
			}

			for (auto e : T)
			{
				result += std::get<2>(e);
			}

			return result;
		}

		bool test1()
		{
			// test case 1
			Graph test_g;
			test_g[1] = std::vector<Edge>
						{std::make_tuple(1, 2, 5),
						 std::make_tuple(1, 3, 1),
						 std::make_tuple(1, 4, 2)
						};
			test_g[2] = std::vector<Edge>
						{std::make_tuple(2, 1, 5),
						 std::make_tuple(2, 4, 4)
						};
			test_g[3] = std::vector<Edge>
						{std::make_tuple(3, 1, 1),
						 std::make_tuple(3, 4, 3)
						};	
			test_g[4] = std::vector<Edge>
						{std::make_tuple(4, 1, 2),
						 std::make_tuple(4, 2, 4),
						 std::make_tuple(4, 3, 3)
						};

			assert(prims_algorithm(test_g) == 7);

			return true;
		}

		void run_algorithm(const std::string& inputFile)
		{
			std::vector<Edge> edges;
			Graph g;

			std::ifstream file(inputFile, std::ios::in);

			if (file.is_open())
			{
				int num_nodes, num_edges;
				file >> num_nodes >> num_edges;

				int snode, dnode, cost;
				while (file >> snode >> dnode >> cost)
				{
					Edge e = std::make_tuple(snode, dnode, cost);
					edges.push_back(e);

					g[snode].push_back(std::make_tuple(snode, dnode, cost));
					g[dnode].push_back(std::make_tuple(dnode, snode, cost));

				}
				file.close();

				// Compute Prim's Minimum Spanning Tree
				long long total_cost = prims_algorithm(g);
				std::cout << "Total cost of Prim's MST is: " << total_cost << std::endl;

				assert(total_cost == -3612829);
			}
		}
	} // namespace
} // namespace
