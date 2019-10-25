#pragma once
#include <chrono>
#include <ctime>
using namespace std::chrono;
namespace EZVisual{
    class Timer{
    public:
        static time_t GetMiroseconds(){
	    	time_point<system_clock, microseconds> tp =
                time_point_cast<microseconds>(system_clock::now());
	    	return duration_cast<microseconds>(tp.time_since_epoch()).count();
	    }
    };
}