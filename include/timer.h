#include <chrono>
#include <iostream>
#include <string>

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

}
