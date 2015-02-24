#ifndef TIMER_H
#define TIMER_H
#include <QTime>

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void start(qint64 offset);
    void stop();
    qint64 getTime();

private:
    QTime timer;
    qint64 startTime;
    qint64 offset;
};

#endif // TIMER_H
