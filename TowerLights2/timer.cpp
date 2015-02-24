#include "timer.h"

Timer::Timer()
{
    startTime = 0;
}

Timer::~Timer()
{

}

void Timer::start(){
    this->offset = 0;
    startTime = time.toMSecsSinceEpoch();
}

void Timer::start(qint64 offset){
    this->offset = offset;
    startTime = time.toMSecsSinceEpoch();
}

void Timer::stop(){
    startTime = 0;
}

qint64 Timer::getTime(){
    return (time.toMSecsSinceEpoch() - startTime) + offset;
}

