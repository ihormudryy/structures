#include <gtest/gtest.h>
#include "unionfind/unionfind.h"
#include <iostream>
#include <fstream>
#include <string>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

using namespace customalgorithms;
using namespace std;

TEST(TestUnionFind, createTiny)
{
    //ifstream myfile("data/uf/tinyUF.txt");
    ifstream myfile("data/uf/largeUF.txt");
    string length;
    getline(myfile, length);
    UnionFind uf(stoi(length));
    string line;
    //uf.print();
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            int sp = line.find(' ');
            int p = stoi(line.substr(0, sp));
            int q = stoi(line.substr(sp, line.length()));

            if(!uf.connected(p, q)) uf.setUnion(p, q);

            //cout << p << " " << q << '\n';
        }
        myfile.close();
        //uf.print();
    }
}
