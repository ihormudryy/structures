#include "../include/unionfind/unionfind.h"
#include <iostream>

using namespace customalgorithms;

UnionFind::UnionFind(int N, alg param)
    : _id(new int[N]),
      _count(N),
      _size(N)
{
    if (_id == nullptr) {
      throw;
    }
    else
    {
        _param = param;
        if (param == WEIGHTED_QUICK_UNION)
            _sz = new int[N];
        for (int i = 0; i < _size; i++)
        {
            if (param == WEIGHTED_QUICK_UNION) _sz[i] = 1;
            _id[i] = i;
        }
    }
}

UnionFind::~UnionFind()
{
    delete _id;
}

void UnionFind::setUnion(int p, int q, alg param)
{
    if (_param != WEIGHTED_QUICK_UNION && param == WEIGHTED_QUICK_UNION)
    {
        std::cerr << "Reinitialize UnionFind object with WEIGHTED_QUICK_UNION parameter";
        throw;
    }

    int _p = find(p);
    int _q = find(q);

    if (_p != _q)
    {
        switch ( _param )
        {
            case (WEIGHTED_QUICK_UNION):
                _wigthedQuickUnion(_p, _q);
                break;
            case (QUICK_UNION):
                _quickUnion(_p, _q);
                break;
            case (QUICK_FIND):
                _quickFind(_p, _q);
                break;
        }
        _count--;
    }
}

int UnionFind::find(int p)
{
    if (_param == QUICK_FIND)
        return _id[p];
    else
    {
        while (p != _id[p]) p = _id[p];
        return p;
    }
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
    std::cout << "id array: ";
    for (int i = 0; i < _size; i++)
        std::cout << _id[i] << " ";
    if(_param == WEIGHTED_QUICK_UNION)
    {
        std::cout << "sz array: ";
        for (int i = 0; i < _size; i++)
            std::cout << _sz[i] << " ";
    }
    std::cout << std::endl;
}

void UnionFind::_quickFind(int p, int q)
{
    for (int i = 0; i < _size; i++)
    {
        if (p == _id[i])
            _id[i] = q;
    }
}

void UnionFind::_wigthedQuickUnion(int p, int q)
{
    if (_sz[p] < _sz[q])
    {
        _id[p] = q;
        _sz[q] += _sz[p];
    }
    else
    {
        _id[q] = p;
        _sz[p] += _sz[q];
    }
}

void UnionFind::_quickUnion(int p, int q)
{
    _id[p] = q;
}
