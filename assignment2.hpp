//
//  assignment2.cpp
//  Algorithms: Design and Analysis, Part 2
//
//  Programming Assignment 2
//
//  Created by Nenad Mancevic on 4/7/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem 2: Clustering
//
/***********************
In this programming problem and the next you'll code up the clustering 
algorithm from lecture for computing a max-spacing k-clustering. 
Download the text file here (http://bit.ly/1NS4nDf). 
This file describes a distance function (equivalently, a complete graph 
with edge costs). It has the following format:
[number_of_nodes]
[edge 1 node 1] [edge 1 node 2] [edge 1 cost]
[edge 2 node 1] [edge 2 node 2] [edge 2 cost]
...
There is one edge (i,j) for each choice of 1≤i<j≤n, where n is the 
number of nodes. For example, the third line of the file is "1 3 5250", 
indicating that the distance between nodes 1 and 3 (equivalently, the cost of the 
edge (1,3)) is 5250. You can assume that distances are positive, but you should 
NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on 
this data set, where the target number k of clusters is set to 4. What is the 
maximum spacing of a 4-clustering?
************************/
//
//  Problem 3: Clustering big
//
/***********************
In this question your task is again to run the clustering algorithm from lecture, 
but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) 
are only defined implicitly, rather than being provided as an explicit list.
The data set is here (http://bit.ly/1JlHzv0). The format is:
[# of nodes] [# of bits for each node's label]
[first bit of node 1] ... [last bit of node 1]
[first bit of node 2] ... [last bit of node 2]
...
For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" 
denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined 
as the Hamming distance--- the number of differing bits --- between 
the two nodes' labels. For example, the Hamming distance between 
the 24-bit label of node #2 above and the label 
"0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 
(since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a 
k-clustering with spacing at least 3? That is, how many clusters are needed 
to ensure that no pair of nodes with all but 2 bits in common get split 
into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you 
probably can't write it out explicitly, let alone sort the edges by cost. 
So you will have to be a little creative to complete this part of the question. 
For example, is there some way you can identify the smallest distances 
without explicitly looking at every pair of nodes?
************************/
#include <string>
#include <fstream>
#include "lib/UnionFind.hpp"
#include <tuple>
#include <algorithm>
#include <list>

namespace assignment2
{
	namespace four_clustering
	{
        int four_clustering(const std::string& inputFile)
        {
            const int K = 4;    // four clusters
            typedef std::tuple<int, int, int> Edge;
            std::vector<Edge> edges;

            std::fstream file(inputFile, std::ios::in);
            if (file.is_open())
            {
                int n;
                int x, y, c;
                file >> n;
                // we'll use UnionFind for computing 4 clusters
                DataStructures::UnionFind uf(n);
                while (file >> x >> y >> c)
                {
                    edges.push_back(std::make_tuple(x, y, c));
                }

                // first step, sort edges in decreasing order of distances (because can't pop from front on std::vector)
                std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)
                {
                    return (std::get<2>(a) > std::get<2>(b));
                });
           
                std::vector<Edge> test1 = {  std::make_tuple(1, 3, 2), std::make_tuple(1, 4, 3), std::make_tuple(1, 2, 1), std::make_tuple(2,4,1) };
            
                while (uf.count() > K)
                {
                    Edge connect = edges.back();                                  // take the min cost edge
                    edges.pop_back();                                            // remove it from the set
                    uf.Union(std::get<0>(connect)-1, std::get<1>(connect)-1);   // and connect the points
                }
                file.close();
                
                // let's loop through the remaining edges and find the first cluster not connected to one of our 4 clusters
                Edge remaining = edges.back();
                while (uf.connected(std::get<0>(remaining)-1, std::get<1>(remaining)-1))
                {
                    edges.pop_back();
                    remaining = edges.back();
                }
                return std::get<2>(remaining);  // just get the edge weight, corresponding to max-spacing
            }
            return -1;
        }
	} // namespace

	namespace clustering_big
	{

	}

} // namespace assignment2
