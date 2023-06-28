#pragma once
#include<iostream>
#include<time.h>
class StopWatch
{
private:
	clock_t startTime;
	clock_t endTime;

public:
	clock_t getStartTime();
	clock_t getEndTime();
	StopWatch();
	void Start();
	void Stop();
	double getElapsedTime();
};

