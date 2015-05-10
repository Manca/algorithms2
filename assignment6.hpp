#pragma once
//
//  assignment6.hpp
//  Algorithms: Design and Analysis, Part 2
//
//  Programming Assignment 6
//
//  Created by Nenad Mancevic on 05/10/15
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem: 2-SAT Problem
//
/***********************
In this assignment you will implement one or more algorithms for the 2SAT problem. 
Here are 6 different 2SAT instances: #1 #2 #3 #4 #5 #6.
The file format is as follows. In each instance, the number of variables and the 
number of clauses is the same, and this number is specified on the first line of the file. 
Each subsequent line specifies a clause via its two literals, with a number denoting 
the variable and a "-" sign denoting logical "not". For example, the second line of 
the first data file is "-16808 75250", which indicates the clause ¬x16808∨x75250.

Your task is to determine which of the 6 instances are satisfiable, and which 
are unsatisfiable. In the box below, enter a 6-bit string, where the ith bit 
should be 1 if the ith instance is satisfiable, and 0 otherwise. For example, 
if you think that the first 3 instances are satisfiable and the last 3 are not, 
then you should enter the string 111000 in the box below.

DISCUSSION: This assignment is deliberately open-ended, and you can implement whichever 
2SAT algorithm you want. For example, 2SAT reduces to computing the strongly connected 
components of a suitable graph (with two vertices per variable and two directed edges 
per clause, you should think through the details). This might be an especially attractive 
option for those of you who coded up an SCC algorithm for my Algo 1 course. 
Alternatively, you can use Papadimitriou's randomized local search algorithm. 
(The algorithm from lecture is probably too slow as stated, so you might want to make o
ne or more simple modifications to it --- even if this means breaking the analysis given in 
lecture --- to ensure that it runs in a reasonable amount of time.) A third approach is 
via backtracking. In lecture we mentioned this approach only in passing; see Chapter 9 
of the Dasgupta-Papadimitriou-Vazirani book, for example, for more details.
----
This problem is solved using a variant of Kosaraju's Strongly Connected Components
algorithm (http://scienceblogs.com/goodmath/2007/10/30/computing-strongly-connected-c/)
3.28 problem (page 106) of Dasgupta's Algorithms (http://beust.com/algorithms.pdf) says:
Given an instance I of 2SAT with n variables and m clauses, construct a directed graph 
GI = (V, E) as follows:
• GI has 2n nodes, one for each variable and its negation.
• GI has 2m edges: for each clause (α ∨ β) of I (where α, β are literals), GI has an edge from
from the negation of α to β, and one from the negation of β to α.
Note that the clause (α ∨ β) is equivalent to either of the implications not α ⇒ β or not β ⇒ α. 
In this sense, GI records all implications in I.
(c) Carry out this construction for the instance of 2SAT given above, and for the instance you
constructed in (b).
(d) Show that if GI has a strongly connected component containing both x and not x for some
variable x, then I has no satisfying assignment.
(e) Now show the converse of (d): namely, that if none of GI ’s strongly connected components
contain both a literal and its negation, then the instance I must be satisfiable. (Hint: Assign
values to the variables as follows: repeatedly pick a sink strongly connected component
of GI . Assign value true to all literals in the sink, assign false to their negations, and
delete all of these. Show that this ends up discovering a satisfying assignment.)
(f) Conclude that there is a linear-time algorithm for solving 2SAT.
***********************/

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include "lib/profile.hpp"

namespace assignment6 
{

    typedef std::unordered_map<int, std::vector<int>> Graph;
    std::stack<int>                  _S;
    std::unordered_map<int, bool>   _explored;
    
    void readFile(const std::string& fileName, Graph& GOrig, Graph& GRev)
    {
        std::ifstream file(fileName, std::ios::in);
        int n;
        file >> n;

        PROFILE("Reading file: " + fileName);
        if (file.is_open())
        {
            int tail, head;
            while (file >> tail >> head)
            {
                // two edges per x,y pair
                GOrig[-tail].push_back(head);   // 1) notX => y
                if (GOrig.count(head) == 0)
                    GOrig[head] = std::vector<int>();

                GOrig[-head].push_back(tail);   // 2) notY => x
                if (GOrig.count(tail) == 0)
                    GOrig[tail] = std::vector<int>();

                // the same for reversed graph
                GRev[head].push_back(-tail);
                if (GRev.count(-tail) == 0)
                    GRev[-tail] = std::vector<int>();

                GRev[tail].push_back(-head);
                if (GRev.count(-head) == 0)
                    GRev[-head] = std::vector<int>();

            }
            file.close();
        }
        PROFILE_STOP();
    }

    void DFSFillStack(Graph& g, int u)
    {
        _explored[u] = true;           // mark  as seen

        // for every edge (s, v)
        for (int v : g[u])
        {
            if (!_explored[v])   // if v is not yet explored
            {
                DFSFillStack(g, v);
            }
        }
        _S.push(u);
    }    

    void DFSSCC(Graph& g, int u, std::vector<int>& scc)
    {
        _explored[u] = true;           // mark  as seen

        // for every edge (u, v)
        for (int v : g[u])
        {
            if (!_explored[v])   // if v is not yet explored
            {
                DFSSCC(g, v, scc);
            }
        }
        scc.push_back(u);   // add node to scc
    }

    bool Check2SAT(Graph& G, Graph& GRev)
    {
        // Kosaraju SCC Algorithm
        // step 1: while stack size less than graph size
        // push elements according to their finish times
        while (_S.size() < G.size())
        {
            for (auto element : G)
            {
                // if not found in stack (not explored), let's DFS
                if (!_explored[element.first])
                {
                    DFSFillStack(G, element.first);
                }
            }
        }
        
        _explored.clear();
        std::vector<std::vector<int>> allSCC;

        // step 2: pop elements from stack and DFS
        // on transposed graph
        while (!_S.empty())
        {
            int el = _S.top();
            _S.pop();
            if (_explored[el])
                continue;

            std::vector<int> scc;
            DFSSCC(GRev, el, scc);
            allSCC.push_back(scc);
        }

        // Prints SCCs on reversed graph
        /*  for (auto vec : allSCC)
        {
        for (int el : vec)
        std::cout << " " << el;
        std::cout << std::endl;
        }*/

        // step 3: added step for 2SAT problem
        // if we find X and not X in SCC then
        // 2SAT is unsatisfiable
        for (auto vec : allSCC)
        {
            for (int i = 0; i < vec.size(); i++)
            {
                for (int j = 0; j < vec.size(); j++)
                    if (vec[i] == -vec[j])
                    {
                        return false;
                    }
            }
        }
        return true;
    }

    bool run_algorithm(const std::string& fileName)
    {
        // load from file
        Graph G, GRev;
        readFile(fileName, G, GRev);
        
        _explored.clear();
        PROFILE("Modified Kosaraju for 2SAT");
        // run algorithm with original and reverse graphs
        bool res = Check2SAT(G, GRev);
        PROFILE_STOP();
        return res;
    }

    void testCase1()
    {
        /*** TEST CASE 1 (3 components, 3 elems each)*/
        Graph G;
        G[1] = { 4 };
        G[2] = { 8 };
        G[3] = { 6 };
        G[4] = { 7 };
        G[5] = { 2 };
        G[6] = { 9 };
        G[7] = { 1 };
        G[8] = { 5, 6 };
        G[9] = { 3, 7 };

        Graph GRev;
        GRev[1] = { 7 };
        GRev[2] = { 5 };
        GRev[3] = { 9 };
        GRev[4] = { 1 };
        GRev[5] = { 8 };
        GRev[6] = { 3, 8 };
        GRev[7] = { 4, 9 };
        GRev[8] = { 2 };
        GRev[9] = { 6 };
        
        Check2SAT(G, GRev);
    }

} // namespace