#include "StopWatch.h"

clock_t StopWatch::getStartTime()
{
	return startTime;
}

clock_t StopWatch::getEndTime()
{
	return endTime;
}

StopWatch::StopWatch()
{
	startTime = clock();
	endTime = 0;
}

void StopWatch::Start()
{
	startTime = clock();
}

void StopWatch::Stop()
{
	endTime = clock();
}

double StopWatch::getElapsedTime()
{
	return ((double)(endTime - startTime));
}
