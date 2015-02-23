#include "timer.h"

Timer::Timer()
{
    startTime = 0;
}

Timer::~Timer()
{

}

void Timer::start(){
    startTime = time.toMSecsSinceEpoch();
}

void Timer::stop(){
    startTime = 0;
}

qint64 Timer::getTime(){
    return time.toMSecsSinceEpoch() - startTime;
}

