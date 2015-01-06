#include <gtest/gtest.h>
#include "unionfind/unionfind.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#define WINDOWS
#endif

using namespace customalgorithms;
using namespace std;
using namespace std::chrono;

typedef milliseconds ms;

ms getMS()
{
    return duration_cast<ms>(high_resolution_clock::now().time_since_epoch());
}

void getTime(int& msec, ms b_time)
{
    ms after = getMS();
    int delta = after.count() - b_time.count();
    cout << delta << "  ";
    msec += delta;
}

void parseFileToUF(ifstream& file, UnionFind::alg param)
{
    string length;
    file.clear();
    file.seekg(0, ios::beg);
    getline(file, length);
    UnionFind uf(stoi(length), param);
    string line;
    int msec = 0;
    ms timer_before = getMS();;
    
    timer_before = getMS();
    while ( getline(file, line) )
    {
        int sp = line.find(' ');
        int p = stoi(line.substr(0, sp));
        int q = stoi(line.substr(sp, line.length()));
        if(!uf.connected(p, q)) uf.setUnion(p, q);
    }
    getTime(msec, timer_before);
    
    if (param == UnionFind::QUICK_FIND)
        cout << param << " UnionFind::QUICK_FIND time  " << msec * 0.001 << " sec" << endl;
    if (param == UnionFind::QUICK_UNION)
		cout << param << " UnionFind::QUICK_UNION time  " << msec * 0.001 << " sec" << endl;
    if (param == UnionFind::WEIGHTED_QUICK_UNION)
		cout << param << " UnionFind::WEIGHTED_QUICK_UNION time  " << msec * 0.001 << " sec" << endl;
	cout << "=======================================================================" << endl;
}

TEST(TestUnionFind, createTiny)
{

	string pref = "";

#ifdef WINDOWS
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
    pref = string(buffer).substr(0, pos) + "/";
#endif 
	
    ifstream mediumFile(pref + "data/uf/mediumUF.txt", ios::ate | ios::in);
	if (mediumFile.is_open())
	{
		cout << "MEDIUM FILE" << endl;
		parseFileToUF(mediumFile, UnionFind::QUICK_FIND);
		parseFileToUF(mediumFile, UnionFind::QUICK_UNION);
		parseFileToUF(mediumFile, UnionFind::WEIGHTED_QUICK_UNION);
		mediumFile.close();
	}
    
    ifstream tiny(pref + "data/uf/tinyUF.txt", ios::ate | ios::in);
	if (tiny.is_open())
	{
		cout << "TINY FILE" << endl;
		parseFileToUF(tiny, UnionFind::QUICK_FIND);
		parseFileToUF(tiny, UnionFind::QUICK_UNION);
		parseFileToUF(tiny, UnionFind::WEIGHTED_QUICK_UNION);
		tiny.close();
	}


    ifstream large(pref + "data/uf/largeUF.txt", ios::ate | ios::in);
	if (large.is_open())
	{
		cout << "LARGE FILE" << endl;
		//parseFileToUF(large, UnionFind::QUICK_UNION);
		//parseFileToUF(large, UnionFind::WEIGHTED_QUICK_UNION);
        //parseFileToUF(large, UnionFind::QUICK_FIND);
		large.close();
	}
	
}
