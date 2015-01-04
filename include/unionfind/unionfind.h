#include <memory>

#ifndef UNIONFIND_H
#define UNIONFIND_H

#pragma once

namespace customalgorithms
{
class UnionFind
{
public:
    UnionFind(int N = 0);
    ~UnionFind();
    void setUnion(int p, int q);
    int find(int p);
    bool connected(int p, int q);
    int count();
    void print();
private:
    int* _id;
    int* _sz;
    int _count;
    int _size;
};
}
#endif // UNIONFIND_H
