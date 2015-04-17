#include <chrono>
#include <iostream>
#include <string>
#include <stack>

#pragma once

using namespace std;

typedef chrono::milliseconds ms;

namespace testtools
{

class Timer
{
public:
    Timer();
    ~Timer();
    void startWatch();
    void stopWatch();
    void addLap();
    void resetWatch();
    int getAverLap();
    int getLastLap();
    string getTime();
    int getElapsedTime();
    int getAverageTime();
private:
    ms _timestamp_start;
    ms _timestamp_end;
    ms _lap_start;
    ms _lap_end;
    int _delta;
    stack<int> _laps;
    ms _timestamp();
};

} // namespace testtools
