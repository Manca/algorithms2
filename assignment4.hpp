#pragma once
//
//  assignment4.hpp
//  Algorithms: Design and Analysis, Part 2
//
//  Programming Assignment 4
//
//  Created by Nenad Mancevic on 4/26/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem: All-Pairs Shortest-Path Algorithms
//
/***********************
In this assignment you will implement one or more algorithms 
for the all-pairs shortest-path problem. 
Here are data files describing three graphs: graph #1 (http://bit.ly/1EED6Fx); 
graph #2 (http://bit.ly/1z7horA); graph #3 (http://bit.ly/1HHaNXt).
The first line indicates the number of vertices and edges, respectively. 
Each subsequent line describes an edge (the first two numbers are its 
tail and head, respectively) and its length (the third number). 
NOTE: some of the edge lengths are negative. 
NOTE: These graphs may or may not have negative-cost cycles.

Your task is to compute the "shortest shortest path". 
Precisely, you must first identify which, if any, 
of the three graphs have no negative cycles. For each such graph, 
you should compute all-pairs shortest paths and remember the 
smallest one (i.e., compute minu,v∈Vd(u,v), where d(u,v) 
denotes the shortest-path distance from u to v).

If each of the three graphs has a negative-cost cycle, 
then enter "NULL" in the box below. If exactly one graph has no 
negative-cost cycles, then enter the length of its shortest 
shortest path in the box below. 
If two or more of the graphs have no negative-cost cycles, 
then enter the smallest of the lengths of their shortest 
shortest paths in the box below.

OPTIONAL: You can use whatever algorithm you like to solve this question. 
If you have extra time, try comparing the performance of different 
all-pairs shortest-path algorithms!

OPTIONAL: If you want a bigger data set to play with, try computing the 
shortest shortest path for this graph (http://bit.ly/1Gw5lXk).
***********************/
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>    // std::min
#include "lib/profile.hpp"

namespace assignment4
{
    typedef std::unordered_map<int, std::vector<std::pair<int,int>>> Graph;    // vertex -> (list of nodes connected to, with edge costs)
    Graph g;

    int load_graph(const std::string& fileName)
    {
        if (!g.empty())
            g.clear();

        std::fstream file(fileName, std::ios::in);
        int n, m;
        
        if (file.is_open())
        {
            file >> n >> m;
            int source, dest, cost;
            while (file >> source >> dest >> cost)
            {
                g[source].push_back(std::make_pair(dest, cost));
            }
            file.close();
        }
        return n;
    }
    // returns edge cost if i,j are connected
    bool ijConnected(int i, int j, const Graph& graph, int& cst)
    {
        std::vector<std::pair<int, int>> neighbors = graph.at(i);
        for (const auto& n : neighbors)
        {
            if (n.first == j)
            {
                cst = n.second;
                return true;
            }
        }
        cst = 0;   // assuming no loops are permitted, we return 0 if they are not connected!
        return false;
    }
    // outputs shortest shortest path
    bool floyd_warshall(Graph& graph, int n, int& shortest)
    {
        PROFILE("Initialize Floyd-Warshall")
        std::vector<std::vector<std::vector<int>>> A;       // a 3D array
        // setup sizes (we will store only kth and k-1th result)
        A.resize(2);
        for (int i = 0; i < 2; i++)
        {
            A[i].resize(n+1);
            for (int j = 0; j <= n; j++)
                A[i][j].resize(n+1);
        }
        
        for (int i = 1; i <= n; i++)             // i,j are vertices (from 1 to 1000)
            for (int j = 1; j <= n; j++)
            {
                int cost;
                if (i == j)   A[0][i][j] = 0;
                else if (ijConnected(i, j, graph, cost)) A[0][i][j] = cost;
                else if (i != j)  A[0][i][j] = INT32_MAX/2 -1;
            }

        PROFILE_STOP();

        // the algorithm
        PROFILE("Floyd-Warshall algorithm");
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    A[1][i][j] = std::min(A[0][i][j], A[0][i][k] + A[0][k][j]);
                    A[0][i][j] = A[1][i][j];    // store currently computed value at zero position (previous - interchange)
                }

                // check for negative cycles (if current i-th iteration reveals cycle, abort!)
                if (A[1][i][i] < 0)
                {
                    std::cout << "Negative cycle!! Vertex: " << i << ". Total weight: " << A[1][i][i] << std::endl;
                    PROFILE_STOP();
                    return false;
                }
            }
           
        }
        PROFILE_STOP();

        // find the shortest shortest path
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                if (A[1][i][j] < shortest) shortest = A[1][i][j];
            }
        }

        return true;
    }

    void run_algorithm(const std::string& fileName)
    {
        int n = load_graph(fileName);
        int shortest_shortest_path = INT32_MAX;
        if (floyd_warshall(assignment4::g, n, shortest_shortest_path))
        {
            std::cout << "Shortest of all shortest paths is: " << shortest_shortest_path << std::endl;
            assert(shortest_shortest_path == -19);
        }
    }

} // namespace