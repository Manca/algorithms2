#pragma once
//
//  UnionFind.hpp - Auxiliary Union-Find data structure implemented as Union by Rank
//
//  Algorithms: Design and Analysis, Part 2
//
//  Created by Nenad Mancevic on 04/09/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>

namespace DataStructures
{
    class UnionFind
    {
    public:
        UnionFind(int n)
        {
           // _parent.resize(n);
           // _rank.resize(n);
            _parent = new int[n];
            _rank = new int[n];

            _count = n;

            for (int i = 0; i < n; i++)
            {
                _parent[i] = i;
                _rank[i] = 0;
            }
        }
        ~UnionFind()
        {
            delete[] _parent;
            delete[] _rank;
        }

        int Find(int x)
        {
            while (_parent[x] != x)
                x = _parent[x];

            return x;
        }

        void Union(int x, int y)
        {
            int s1 = Find(x);
            int s2 = Find(y);

            // if both elements belong to the same component return
            if (s1 == s2)
                return;

            if (_rank[s1] > _rank[s2])
                _parent[s2] = s1;
            else if (_rank[s1] < _rank[s2])
                _parent[s1] = s2;
            else
            {
                _rank[s1]++;
                _parent[s2] = s1;
            }
            _count--;
        }

        int count()
        {
            return _count;
        }

        bool connected(int x, int y)
        {
            return Find(x) == Find(y);
        }
    private:
        //std::vector<int>    _parent;
        //std::vector<int>    _rank;
        int*                _parent;
        int*                _rank;
        int                 _count;
    };

    bool TestCase1()
    {
        // test on 10 elements starting from 0
        UnionFind uf(10);

        assert(uf.Find(0) == 0);
        assert(uf.Find(9) == 9);

        uf.Union(0, 9);
        assert(uf.Find(9) == 0);
        assert(uf.count() == 9);

        uf.Union(9, 3);
        assert(uf.Find(9) == 0);
        assert(uf.count() == 8);

        uf.Union(4, 5);
        uf.Union(4, 9);
        uf.Union(5, 7);
        assert(uf.Find(9) == 4);
        assert(uf.Find(3) == 4);
        assert(uf.Find(0) == 4);
        uf.Union(3, 4);
        assert(uf.count() == 5);
        uf.Union(0, 7);
        assert(uf.count() == 5);

        return true;
    }

    void TestCase2(const std::string inputFile)
    {
        std::ifstream file(inputFile, std::ios::in);

        if (file.is_open())
        {
            int n, x, y;
            file >> n;
            UnionFind uf(n);

            while (file >> x >> y)
            {
                uf.Union(x, y);
            }
            file.close();
        }
    }
} // namespace
