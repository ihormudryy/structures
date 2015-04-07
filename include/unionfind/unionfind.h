#include <memory>

#ifndef UNIONFIND_H
#define UNIONFIND_H

#pragma once

#ifndef nullptr
#define nullptr NULL
#endif // nullptr

namespace customalgorithms
{

class UnionFind
{
public:
    enum alg{
        QUICK_UNION,
        QUICK_FIND,
        WEIGHTED_QUICK_UNION
    };
    UnionFind(int N = 0, alg a = QUICK_FIND);
    ~UnionFind();
    void setUnion(int p, int q, alg a = QUICK_FIND);
    int find(int p);
    bool connected(int p, int q);
    int count();
    void print();

private:
    alg _param;
    int* _id;
    int* _sz;
    int _count;
    int _size;
    void _quickUnion(int p, int q);
    void _quickFind(int p, int q);
    void _wigthedQuickUnion(int p, int q);
};

}
#endif // UNIONFIND_H
