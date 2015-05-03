#pragma once
//
//  assignment5.hpp
//  Algorithms: Design and Analysis, Part 2
//
//  Programming Assignment 5
//
//  Created by Nenad Mancevic on 4/26/15 (done on 05/04/15).
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem: Traveling Salesman Problem
//
/***********************
In this assignment you will implement one or more algorithms for the 
traveling salesman problem, such as the dynamic programming algorithm 
covered in the video lectures. 
Here is a data file (http://bit.ly/1bVhBE2) describing a TSP instance. 
The first line indicates the number of cities. 
Each city is a point in the plane, and each subsequent line indicates 
the x- and y-coordinates of a single city.
The distance between two cities is defined as the Euclidean distance 
that is, two cities at locations (x,y) and (z,w) have distance 
sqrt((x−z)^2+(y−w)^2) between them.

In the box below, type in the minimum cost of a traveling salesman tour
for this instance, rounded down to the nearest integer.

OPTIONAL: If you want bigger data sets to play with, check out the 
TSP instances from around the world here. The smallest data set 
(Western Sahara) has 29 cities, and most of the data sets are 
much bigger than that. What's the largest of these data sets that 
you're able to solve --- using dynamic programming or, if you like, 
a completely different method?

HINT: You might experiment with ways to reduce the data set size. 
For example, trying plotting the points. Can you infer any structure 
of the optimal solution? Can you use that structure to speed up your algorithm?
***********************/
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>

namespace assignment5
{
    class TSP
    {
    public:
        TSP(const std::string& fileName)
        {
            std::fstream file(fileName, std::ios::in);

            if (file.is_open())
            {
                file >> num_cities;
                float x, y;
                while (file >> x >> y)
                    city_coord.push_back(std::make_pair(x, y));
                file.close();
            }
            _distances.resize(num_cities);
            for (int i = 0; i < num_cities; i++)
                _distances[i].resize(num_cities);

            precalculate_distances();
        }
        float euclid_distance(std::pair<float, float> a, std::pair<float, float> b)
        {
            return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
        }
        void precalculate_distances()
        {
            for (int i = 0; i < num_cities; i++)
                for (int j = 0; j < num_cities; j++)
                {
                    _distances[i][j] = euclid_distance(city_coord[i], city_coord[j]);
                }
        }
        // returns the cost of the min cost tour for the given graph
        double solve()
        {         
            ////// array definition
            int S_size = (int)std::pow(2, num_cities-1); // 2^24 (first city is always included)
            float **A = new float*[S_size];
            for (int i = 0; i < S_size; i++)
            {
                A[i] = new float[num_cities-1];         // 2^24 x 24
            }

            // initialization
            for (int i = 0; i < S_size; i++)
            {
                for (int j = 0; j < num_cities-1;j++)
                    A[i][j] = (float)INT32_MAX;
            }
            A[0][0] = 0;    // first subset of S (subset 1), contains only starting vertex 0 (0...001)
            
            // algo
            for (int m = 1; m < num_cities; m++)    // we need to start from 1 to get all the cities that are connected to city 0 directly!
            {
                int64_t S = (1 << m) - 1;    // we begin with initial number of ones (m=2) (2^m - 1 - init size of the set)
                int64_t S_no_j = 0;         // previous S that does not contain j

                while (S < (1 << (num_cities-1)))   // and generate all subsets with m ones in them until we hit 2^(num_cities-1)
                {
                    // let's find all the ones in S and use their positions as vertex numbers
                  //  std::cout << "Subset: " << S << std::endl << "------" << std::endl;
                    for (int j = 0; j < num_cities-1; j++)      // for each city, see if it's in S, and yes do the math! (j+1 actual city number!)
                    {
                        int sXORj = S ^ (1 << j);               // S xor 2^j (put 1 at j's position)
                        // extract last bit
                        bool isJinS = !((sXORj >> j) & 1);      // get the xor'ed bit and AND it with 1 to see if it's 1 or 0
                        if (isJinS)
                        {
                            // do work
                           // std::cout << "Processing city j: " << j+1 << std::endl;
                            float min = (float)INT32_MAX;

                            S_no_j = S ^ (1 << j);
                            std::vector<float> dists(num_cities, (float)INT32_MAX);   // distances
                            dists[0] = A[S_no_j][0] + _distances[0][j+1];

                            for (int k = 0; k < num_cities-1; k++)
                            {
                                if (k != j)
                                {
                                    // need to check if k is in S!
                                    int sXORk = S ^ (1 << k);  // S xor 2^k (put 1 at k's position)
                                    bool isKinS = !((sXORk >> k) & 1);
                                    if (isKinS)
                                    {
                                  //      std::cout << "S without j is: " << S_no_j << std::endl;
                                        dists[k+1] = A[S_no_j][k+1] + _distances[k+1][j+1];
                                    }
                                }
                            }
                            // find min
                            for (int i = 0; i < num_cities; i++)
                                if (dists[i] < min)
                                    min = dists[i];
                           // std::cout << "Minimum for subset: " << S << " is: " << min << std::endl << "-----" << std::endl;
                            A[S][j+1] = min;

                        }
                    }
                    // use Gosper Hack to get the next subset
                    S = next_subset(S);
                }
            }

            // finally, let's get the minimum of all minimums
            float min_min = (float)INT32_MAX;
            for (int j = 1; j < num_cities; j++)
            {
                float calc = A[S_size-1][j] + _distances[j][0];
                if (calc < min_min)
                    min_min = calc;
            }
            std::cout << "Minimum cost tour is: " << min_min << std::endl;

            // cleanup
            for (int i = 0; i < S_size; i++)
            {
                delete[] A[i];
            }
            delete[] A;

            return min_min;
        }

        // Gosper Hack
        int64_t next_subset(int64_t x)
        {
            int64_t y = x & -x;
            int64_t c = x + y;
            x = (((x ^ c) >> 2) / y) | c;
            return x;
        }

    private:
        int num_cities;
        std::vector<std::pair<float, float>> city_coord;
        std::vector<std::vector<float>> _distances;
    };
} // namespace