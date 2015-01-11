#include <chrono>
#include <iostream>
#include <string>

#ifndef __TIMER__H
#define __TIMER__H

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

using namespace std;

typedef chrono::milliseconds ms;

namespace customalgorithms
{
class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    string getTime();
    int getTimeDelta();

private:
    ms _timestamp_start;
    ms _timestamp_end;
    int _delta;
};

#if  defined( __EMSCRIPTEN__ ) && !defined( TESTING_MODE_H )
EMSCRIPTEN_BINDINGS(timer_example) {
    class_<Timer>("Timer")
        .constructor()
        .function("start", &Timer::start)
        .function("stop", &Timer::stop)
        .function("getTime", &Timer::getTime)
        ;
}
#endif //__EMSCRIPTEN__
}

#endif // __TIMER__H
