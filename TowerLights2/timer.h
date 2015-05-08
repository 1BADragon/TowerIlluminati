/*! \file timer.h
 * \brief This file class defines the Timer class
 */

#ifndef TIMER_H
#define TIMER_H
#include <QTime>
/*!
 * \brief The Timer class
 */

/*!
 * This class is used in the case that there is
 * no audio file. It is used as a timer to keep the
 * frames in sync with a time format. This classes uses
 * the QTime library to extract time data from the OS.
 */
class Timer
{
public:
    //! Constructor
    Timer();
    //! Deconstructor
    ~Timer();
    //! Starts the timer at 0
    void start();
    //! Starts the timer at offset
    void start(qint64 offset);
    //! Stops the timer
    void stop();
    //! Returns the current time; 0 if not started
    qint64 getTime();

private:
    //! the timer class from Qt
    QTime timer;
    //! startTime used for calculating time elapsed
    qint64 startTime;
    //! offset used in start(offset)
    qint64 offset;
};

#endif // TIMER_H
