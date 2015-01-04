#include "../include/unionfind/unionfind.h"
#include <iostream>

using namespace customalgorithms;

UnionFind::UnionFind(int N)
    : _id(new int[N]),
      _count(N),
      _size(N),
      _sz(new int[N])
{
    if (_id == nullptr) {
      // error assigning memory. Take measures.
      throw;
    }
    else
        for (int i = 0; i < _size; i++)
        {
            _sz[i] = 1;
            _id[i] = i;
        }
}

UnionFind::~UnionFind()
{
    delete _id;
}

void UnionFind::setUnion(int p, int q)
{
    int _p = find(p);
    int _q = find(q);

    if (_p != _q)
    {
        /*
         * Quick search example O(N)=N^2
        for (int i = 0; i < _size; i++)
        {
            if (_p == _id[i])
                _id[i] = _q;
        }
        */

        /* Quick merge algorithm
        _id[_p] = _q;
        */

        if (_sz[_p] < _sz[_q])
        {
            _id[_p] = _q;
            _sz[_q] += _sz[_p];
        }
        else
        {
            _id[_q] = _p;
            _sz[_p] += _sz[_q];
        }
        _count--;
    }
}

int UnionFind::find(int p)
{
    /*
     *
    return _id[p];
    */
    while (p != _id[p]) p = _id[p];
    return p;
}

bool UnionFind::connected(int p, int q)
{
    return find(p) == find(q);
}

int UnionFind::count()
{
    return _count;
}

void UnionFind::print()
{
    for (int i = 0; i < _size; i++)
        std::cout << _id[i] << " ";
    std::cout << std::endl;
}
