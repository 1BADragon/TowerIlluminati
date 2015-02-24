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
    timer.start();
}

void Timer::start(qint64 offset){
    this->offset = offset;
    timer.start();
}

void Timer::stop(){
    startTime = 0;
}

qint64 Timer::getTime(){
    return timer.elapsed() + offset;
}

