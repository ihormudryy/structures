#include <timer.h>

namespace testtools
{

Timer::Timer(){}

Timer::~Timer(){}

string Timer::getTime()
{
	int delta = _timestamp_end.count() - _timestamp_start.count();
    int hours = (delta / (1000*60*60)) % 24;
    int minutes = (delta / (1000*60)) % 60;
    int sec = (delta / 1000) % 60;
    int ms = delta % 1000;
    string s = "";
#ifndef __ANDROID__
	s = to_string(hours) + "h " +
        to_string(minutes) + "m " +
        to_string(sec) + "s " +
        to_string(ms) + "ms \n";
#endif
	return s;
}

int Timer::getElapsedTime()
{
    return _delta;
}

int Timer::getAverageTime()
{
    int a = 0;
    int vals = 0;
    while(_laps.size() > 0)
    {
        vals += _laps.top();
        _laps.pop();
        a++;
    };
    return vals/a;
}

ms Timer::_timestamp()
{
    return chrono::duration_cast<ms>(
                chrono::high_resolution_clock::now().time_since_epoch()
                );
}

void Timer::startWatch()
{
    _timestamp_start = _lap_start = _timestamp();
}

void Timer::stopWatch()
{
    _timestamp_end = _timestamp();
    _delta = _timestamp_end.count() - _timestamp_start.count();
}

void Timer::addLap()
{
    _lap_end = _timestamp();
    _laps.push(_lap_end.count() - _lap_start.count());
    _lap_start = _timestamp();
}

void Timer::resetWatch()
{
    _timestamp_start = _lap_start =_timestamp();
}

int Timer::getLastLap()
{
    int r = _laps.top();
    _laps.pop();
    return r;
}

}
