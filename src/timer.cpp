#include "../include/timer.h"

using namespace customalgorithms;

string Timer::getTime()
{
	int delta = _timestamp_end.count() - _timestamp_start.count();
    int hours = (delta / (1000*60*60)) % 24;
    int minutes = (delta / (1000*60)) % 60;
    int sec = (delta / 1000) % 60;
    int ms = delta % 1000;
	//int days = hours / 24;
	string s;
	s = //to_string(days) + "days " +
        to_string(hours) + "h " +
        to_string(minutes) + "m " +
        to_string(sec) + "s " +
        to_string(ms) + "ms \n";
	return s;
}

int Timer::getTimeDelta()
{
	return _delta;
}

void Timer::start()
{
	_timestamp_start = chrono::duration_cast<ms>(chrono::high_resolution_clock::now().time_since_epoch());
}

void Timer::stop()
{
	_timestamp_end = chrono::duration_cast<ms>(chrono::high_resolution_clock::now().time_since_epoch());
	_delta = _timestamp_end.count() - _timestamp_start.count();
}
