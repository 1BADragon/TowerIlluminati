#ifndef TIMER_H
#define TIMER_H
#include <QDateTime>

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    qint64 getTime();

private:
    QDateTime time;
    qint64 startTime;
};

#endif // TIMER_H
